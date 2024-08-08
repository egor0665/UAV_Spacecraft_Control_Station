#include "vehicle.h"

Vehicle::Vehicle()
{

}

void Vehicle::init(AttitudeInfo vehicleAttitude, TextRenderer *textRenderer)
{
    initializeOpenGLFunctions();
    this->vehicleAttitude = vehicleAttitude;
    this->textRenderer = textRenderer;
    vehicleModel = objLoader::Instance().load("C:/Qt/5.15.2/mingw81_32/GroundControlStation/drone2.obj");
    LoadGLTextures();
}

void Vehicle::draw(float sceneDistanceMultiplier)
{
    glPushMatrix();

    glTranslatef(vehicleAttitude.x/ sceneDistanceMultiplier, vehicleAttitude.y/ sceneDistanceMultiplier, vehicleAttitude.z/ sceneDistanceMultiplier);

    glRotatef(vehicleAttitude.xRot,1,0,0);
    glRotatef(vehicleAttitude.yRot,0,1,0);
    glRotatef(vehicleAttitude.zRot,0,0,1);

    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glColor4f(1.00f, 1.00f, 1.00f, 1.0f);

        glVertex3f(0,  0,  0);
        glVertex3f(0,  0,  2);

    glEnd();

    glColor4f(1.00f, 1.00f, 1.00f, 1.0f);

    glCallList(vehicleModel);

    glPopMatrix();
}

void Vehicle::changeVehicleAttitude(AttitudeInfo vehicleAttitude)
{
    this->vehicleAttitude = vehicleAttitude;
}

void Vehicle::changeVehiclePos(float x, float y, float z)
{
    vehicleAttitude.x = x;
    vehicleAttitude.y = -z;
    vehicleAttitude.z = y;
}

void Vehicle::changeVehicleRot(float xRotRad, float yRotRad, float zRotRad)
{
    const float radToDeg = 57.3;
    const float simErrorY = 90;
    vehicleAttitude.xRot = - xRotRad * radToDeg;
    vehicleAttitude.yRot = - yRotRad * radToDeg + simErrorY;
    vehicleAttitude.zRot = - zRotRad * radToDeg;
}


void Vehicle::changeStatus(int custom_mode, int system_status, int base_mode)
{
    vehicleMode = FLIGHT_MODES[custom_mode];
    systemStatus = SYSTEM_STATUSES[system_status];
    if ((base_mode & MAV_MODE_FLAG_STABILIZE_ENABLED)/MAV_MODE_FLAG_STABILIZE_ENABLED)
        vehicleMode = "Stabilize";
    else if ((base_mode & MAV_MODE_FLAG_GUIDED_ENABLED)/MAV_MODE_FLAG_GUIDED_ENABLED)
        vehicleMode = "Guided";
    else if ((base_mode & MAV_MODE_FLAG_AUTO_ENABLED)/MAV_MODE_FLAG_AUTO_ENABLED)
        vehicleMode = "Auto";
    else if ((base_mode & MAV_MODE_FLAG_TEST_ENABLED)/MAV_MODE_FLAG_TEST_ENABLED)
        vehicleMode = "Preflight";

    armed = (base_mode & MAV_MODE_FLAG_SAFETY_ARMED)/MAV_MODE_FLAG_SAFETY_ARMED;
}

void Vehicle::displayVehicleStatus()
{
    int startY = 30;
    QString armedString;
    if (armed)
        armedString = "Вкл.";
    else
        armedString = "Выкл.";

    textRenderer->renderTextAbsolute(0,
                       startY,
                       0, "X: " + QString::number(vehicleAttitude.x,'f',2),
                       QColor(200,0,0),
                       QFont("Helvetica", 20, QFont::Bold));
    textRenderer->renderTextAbsolute(0,
                       startY + 30,
                       0, "Y: " + QString::number(vehicleAttitude.y,'f',2),
                       QColor(0,200,0),
                       QFont("Helvetica", 20, QFont::Bold));
    textRenderer->renderTextAbsolute(0,
                       startY + 60,
                       0, "Z: " + QString::number(vehicleAttitude.z,'f',2),
                       QColor(0,0,200),
                       QFont("Helvetica", 20, QFont::Bold));

    textRenderer->renderTextAbsolute(0,
                       startY + 80,
                       0, "Режим: " + vehicleMode,
                       QColor("#E1E2E2"));
    textRenderer->renderTextAbsolute(0,
                       startY + 100,
                       0, "Статус: " + systemStatus,
                       QColor("#E1E2E2"));
    textRenderer->renderTextAbsolute(0,
                       startY + 120,
                       0, "Моторы: " + armedString,
                       QColor("#E1E2E2"));
}

void Vehicle::LoadGLTextures()
{
    glGenTextures(1,&vehicleTextures);
    QImage texture1;

    texture1.load("C:/Qt/5.15.2/mingw81_32/GroundControlStation/DroneTexture.png");
    InitGLTexture(texture1, vehicleTextures);
}


void Vehicle::InitGLTexture(QImage textureImage, GLuint texture)
{
    textureImage.convertTo(QImage::Format_RGBA8888);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,GLsizei(textureImage.width()),
                 GLsizei(textureImage.height()),
                 0,
                 GL_RGBA,GL_UNSIGNED_BYTE,
                 textureImage.bits());
}



const AttitudeInfo &Vehicle::getVehicleAttitude() const
{
    return vehicleAttitude;
}

