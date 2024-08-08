#ifndef VEHICLEPOSITIONDISPLAYWIDGET_H
#define VEHICLEPOSITIONDISPLAYWIDGET_H
//#include "customwidget.h"
#include "custom_widgets/tabmodule.h"

#include "helplines.h"
#include "marker.h"
#include "planroute.h"
#include "scene.h"
#include "startpoint.h"
#include "textrenderer.h"
#include "vehicle.h"
#include "vehicleroute.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>
#include <mavlink/ardupilotmega/mavlink.h>
#include <PositionStructs.h>
#include <QtOpenGL>
#include <custom_widgets/Mission_planning_tab_widgets/missionplanitem.h>

const int IDLE_TIMER_INTERVAL = 200;
const int ROUTE_TIMER_INTERVAL = 1000;

class VehiclePositionDisplayWidget: public QOpenGLWidget, public tabModule
{
    Q_OBJECT

    Scene scene;
    Marker marker;
    StartPoint startPoint;
    TextRenderer textRenderer;
    Vehicle vehicle;
    VehicleRoute vehicleRoute;
    PlanRoute planRoute;
    HelpLines helpLines;

    GLfloat sceneDistanceMultiplier = 1;

    GLdouble LAeyes[3]={10,5,10}, LAcenter[3]={0,0,0}, LAup[3]={0,1,0};

    QPoint mousePos;
    GLfloat imgZoom=-20;
    GLfloat XmouseRot = 0, YmouseRot = 0;

    QTimer idleUpdateTimer;
    QTimer routeTimer;
public:


    VehiclePositionDisplayWidget(QWidget *parent = nullptr);
    ~VehiclePositionDisplayWidget();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void setRotations(int x, int y, int z);
    void updatePosition(mavlink_attitude_t message);
    void setPosition(float x, float y, float z);
    void setSleep(bool setSleep);
    void updateHeartBeat(mavlink_heartbeat_t message);
    void updateHomePosition(mavlink_home_position_t message);
    void updateMissionPlan(QVector<MissionPlanItem> planItems);

    void setMarkerMap(QVector<QVector<char>> markerMap, QVector<MarkerInfo> markerInfoVector);
    AttitudeInfo getVehicleAttitude();

protected:
    void InitGLTexture(QImage textureImage, GLuint texture);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent *event) override;
    void checkSceneMultiplier();
    void initOpenGLObjects();
protected slots:
    void updateRoute();
    void updateImage();
};

#endif // VEHICLEPOSITIONDISPLAYWIDGET_H
