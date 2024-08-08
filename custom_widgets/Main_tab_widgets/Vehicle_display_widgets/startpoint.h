#ifndef STARTPOINT_H
#define STARTPOINT_H

#include "textrenderer.h"

#include <QOpenGLExtraFunctions>
#include <PositionStructs.h>

class StartPoint: protected QOpenGLExtraFunctions
{
    AttitudeInfo attitude;
    TextRenderer *textRenderer = nullptr;
public:
    StartPoint();
    void init(AttitudeInfo attitude, TextRenderer *textRenderer);
    void draw(float sceneDistanceMultiplier);
    void changeAttitude(AttitudeInfo newAttitude);

};

#endif // STARTPOINT_H
