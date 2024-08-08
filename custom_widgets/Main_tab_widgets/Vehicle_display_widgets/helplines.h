#ifndef HELPLINES_H
#define HELPLINES_H

#include <QOpenGLExtraFunctions>
#include <PositionStructs.h>
#include "textrenderer.h"

class HelpLines: protected QOpenGLExtraFunctions
{
    TextRenderer *textRenderer;
public:
    HelpLines();
    void init(TextRenderer *textRenderer);
    void draw(Offset sceneOffset, AttitudeInfo vehicleAttitude, float sceneDistanceMultiplier);
};

#endif // HELPLINES_H
