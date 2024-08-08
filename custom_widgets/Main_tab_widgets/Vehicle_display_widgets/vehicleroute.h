#ifndef VEHICLEROUTE_H
#define VEHICLEROUTE_H

#include <QOpenGLExtraFunctions>
#include <PositionStructs.h>
#include "textrenderer.h"

class VehicleRoute: protected QOpenGLExtraFunctions
{
    QVector<PositionInfo> routeVector = {};
    TextRenderer *textRenderer;

public:
    VehicleRoute();
    void draw(float sceneDistanceMultiplier);
    void init(TextRenderer *textRenderer);
    void addRoutePoint(PositionInfo position);
};

#endif // VEHICLEROUTE_H
