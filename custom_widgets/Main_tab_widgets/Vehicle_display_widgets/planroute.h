#ifndef PLANROUTE_H
#define PLANROUTE_H

#include <QOpenGLExtraFunctions>
#include <PositionStructs.h>
#include <custom_widgets/Mission_planning_tab_widgets/missionplanitem.h>
#include "textrenderer.h"

class PlanRoute: protected QOpenGLExtraFunctions
{
    QVector<MissionPlanItem> planItems = {};
    TextRenderer *textRenderer;
public:
    PlanRoute();
    void draw(float sceneDistanceMultiplier, AttitudeInfo vehicleAttitude);
    void init(TextRenderer *textRenderer);
    void changePlanRoute(QVector<MissionPlanItem> planItems);
};

#endif // PLANROUTE_H
