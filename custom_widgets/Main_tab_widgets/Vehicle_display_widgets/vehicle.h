#ifndef VEHICLE_H
#define VEHICLE_H


#include <QOpenGLExtraFunctions>
#include <PositionStructs.h>
#include <QTimer>
#include "objloader.h"
#include "textrenderer.h"
#include "structs.h"

class Vehicle: protected QOpenGLExtraFunctions
{
    TextRenderer *textRenderer;
    GLuint vehicleModel;
    GLuint vehicleTextures;
    AttitudeInfo vehicleAttitude;
    bool armed;
    QString vehicleMode;
    QString systemStatus;
public:
    Vehicle();
    void init(AttitudeInfo vehicleAttitude, TextRenderer *textRenderer);
    void draw(float sceneDistanceMultiplier);
    void changeVehicleAttitude(AttitudeInfo vehicleAttitude);
    const AttitudeInfo &getVehicleAttitude() const;
    void changeVehiclePos(float x, float y, float z);
    void changeVehicleRot(float xRot, float yRot, float zRot);
    void changeStatus(int custom_mode, int system_status, int base_mode);
    void displayVehicleStatus();

protected:
    void LoadGLTextures();
    void InitGLTexture(QImage textureImage, GLuint texture);
};

#endif // VEHICLE_H

