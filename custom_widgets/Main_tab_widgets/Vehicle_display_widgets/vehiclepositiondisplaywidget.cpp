#include "vehiclepositiondisplaywidget.h"
#include <QtOpenGL/QGL>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QFont>
#include <QtMath>
#include <custom_widgets/Mission_planning_tab_widgets/missionplanitem.h>
#include "objloader.h"
#include <customfilemanager.h>
#include <structs.h>

#pragma comment (lib,"opengl32.lib");
#pragma comment (lib,"GlU32.lib");

VehiclePositionDisplayWidget::VehiclePositionDisplayWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    connect(&idleUpdateTimer, SIGNAL(timeout()), this, SLOT(updateImage()));
    idleUpdateTimer.start(IDLE_TIMER_INTERVAL);

    connect(&routeTimer, &QTimer::timeout, this, &VehiclePositionDisplayWidget::updateRoute);
    routeTimer.start(ROUTE_TIMER_INTERVAL);
}


VehiclePositionDisplayWidget::~VehiclePositionDisplayWidget()
{

}

void VehiclePositionDisplayWidget::updateImage()
{
    update();
}

void VehiclePositionDisplayWidget::initializeGL()
{
    initOpenGLObjects();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.11372,0.13333,0.15686,0);


    glEnable(GL_MULTISAMPLE);

    glEnable(GL_TEXTURE_3D);
    glEnable(GL_CULL_FACE);

    glClearDepth(1.0);

    glDepthFunc(GL_LESS);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void VehiclePositionDisplayWidget::initOpenGLObjects()
{
    textRenderer.init(this);
    marker.init(&textRenderer);
    startPoint.init(AttitudeInfo(0,0,0,0,0,0),&textRenderer);

    const GLfloat totalSceneDist = 50.0f;
    const GLfloat XsceneOffset = -25.0f;
    const GLfloat ZsceneOffset = -25.0f;
    const GLfloat YsceneOffset = -25.0f;
    const Offset sceneOffset(XsceneOffset, YsceneOffset, ZsceneOffset);
    const GLfloat numSceneLines = 5;
    scene.init(totalSceneDist, sceneOffset, numSceneLines, &textRenderer);

    vehicle.init(AttitudeInfo(0,0,0,0,0,0),&textRenderer);
    vehicleRoute.init(&textRenderer);

    planRoute.init(&textRenderer);

    helpLines.init(&textRenderer);
}

void VehiclePositionDisplayWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    qreal aspectratio = qreal(w)/qreal(h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0,aspectratio,0.1,200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void VehiclePositionDisplayWidget::checkSceneMultiplier()
{
    Offset sceneOffset = scene.getSceneOffset();
    AttitudeInfo vehicleAttitude = vehicle.getVehicleAttitude();

        if ((abs(vehicleAttitude.x)  >= abs(sceneOffset.xOffset * sceneDistanceMultiplier)))
            sceneDistanceMultiplier *= 1.1;
        else if ((abs(vehicleAttitude.y) >= abs(sceneOffset.yOffset * sceneDistanceMultiplier)))
            sceneDistanceMultiplier *= 1.1;
        else if ((abs(vehicleAttitude.z) >= abs(sceneOffset.zOffset * sceneDistanceMultiplier)))
            sceneDistanceMultiplier *= 1.1;

        else if ((abs(sceneOffset.xOffset * sceneDistanceMultiplier) > abs(sceneOffset.xOffset)) && (abs(vehicleAttitude.x) < abs(sceneOffset.xOffset * sceneDistanceMultiplier / 1.4641)))
                if ((abs(sceneOffset.yOffset * sceneDistanceMultiplier) > abs(sceneOffset.yOffset)) && (abs(vehicleAttitude.y) < abs(sceneOffset.yOffset * sceneDistanceMultiplier / 1.4641)))
                    if ((abs(sceneOffset.zOffset * sceneDistanceMultiplier) > abs(sceneOffset.zOffset)) && (abs(vehicleAttitude.z) < abs(sceneOffset.zOffset * sceneDistanceMultiplier / 1.4641)))
                    sceneDistanceMultiplier /= 1.1;
}

void VehiclePositionDisplayWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    AttitudeInfo vehicleAttitude = vehicle.getVehicleAttitude();

    gluLookAt(vehicleAttitude.x / sceneDistanceMultiplier + cos(0.01 * YmouseRot) * (-imgZoom),
            vehicleAttitude.y / sceneDistanceMultiplier + 0.1 * XmouseRot,
            vehicleAttitude.z / sceneDistanceMultiplier + sin(0.01 * YmouseRot) * (-imgZoom),
            vehicleAttitude.x / sceneDistanceMultiplier,
            vehicleAttitude.y / sceneDistanceMultiplier,
            vehicleAttitude.z / sceneDistanceMultiplier,
            LAup[0],
            LAup[1],
            LAup[2]);

    checkSceneMultiplier();

    scene.draw(sceneDistanceMultiplier);

    Offset sceneOffset = scene.getSceneOffset();
    helpLines.draw(sceneOffset, vehicleAttitude, sceneDistanceMultiplier);

    startPoint.draw(sceneDistanceMultiplier);
    marker.draw(sceneDistanceMultiplier);
    planRoute.draw(sceneDistanceMultiplier,vehicleAttitude);

    vehicleRoute.draw(sceneDistanceMultiplier);

    vehicle.draw(sceneDistanceMultiplier);
    vehicle.displayVehicleStatus();

}

void VehiclePositionDisplayWidget::updateRoute()
{
    AttitudeInfo vehicleAttitude = vehicle.getVehicleAttitude();
    vehicleRoute.addRoutePoint(PositionInfo(vehicleAttitude.x, vehicleAttitude.y, vehicleAttitude.z));

}

void VehiclePositionDisplayWidget::updateHeartBeat(mavlink_heartbeat_t message)
{
    vehicle.changeStatus(message.custom_mode, message.system_status, message.base_mode);
}

void VehiclePositionDisplayWidget::mousePressEvent(QMouseEvent *mo)
{
    mousePos = mo->pos();
}

void VehiclePositionDisplayWidget::mouseMoveEvent(QMouseEvent *mo)
{
    XmouseRot += 0.1/ 3.14159 * (mo->pos().y()-mousePos.y());
    YmouseRot += 0.1/ 3.14159 * (mo->pos().x()-mousePos.x());
    update();
}

void VehiclePositionDisplayWidget::wheelEvent(QWheelEvent *event)
{
    imgZoom += event->angleDelta().ry() / 100;
    if (imgZoom>=-1) imgZoom = -1;
    update();
}

void VehiclePositionDisplayWidget::updateMissionPlan(QVector<MissionPlanItem> planItems)
{
    planRoute.changePlanRoute(planItems);
}

void VehiclePositionDisplayWidget::updatePosition(mavlink_attitude_t message)
{
    vehicle.changeVehicleRot(message.roll, message.yaw, message.pitch);
}

void VehiclePositionDisplayWidget::updateHomePosition(mavlink_home_position_t message)
{
//    routeVector.clear();
    startPoint.changeAttitude(AttitudeInfo(message.x,-message.z,message.y,0,0,0));
}

void VehiclePositionDisplayWidget::setSleep(bool setSleep)
{
    this->sleep = sleep;
    if (setSleep)
    {
        idleUpdateTimer.stop();
        routeTimer.stop();
    }
    else
    {
        idleUpdateTimer.start(IDLE_TIMER_INTERVAL);
        routeTimer.start(ROUTE_TIMER_INTERVAL);
    }
}

void VehiclePositionDisplayWidget::setPosition(float x, float y, float z)
{
    vehicle.changeVehiclePos(x,y,z);
}

void VehiclePositionDisplayWidget::setMarkerMap(QVector<QVector<char>> markerMap, QVector<MarkerInfo> markerInfoVector)
{
    marker.changeMarkerMap(markerMap,markerInfoVector);
}

AttitudeInfo VehiclePositionDisplayWidget::getVehicleAttitude()
{
    return vehicle.getVehicleAttitude();
}
