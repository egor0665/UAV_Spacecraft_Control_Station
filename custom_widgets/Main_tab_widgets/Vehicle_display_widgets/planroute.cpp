#include "planroute.h"
#include <GL/gl.h>
#include <GL/glu.h>

PlanRoute::PlanRoute()
{

}

void PlanRoute::draw(float sceneDistanceMultiplier, AttitudeInfo vehicleAttitude)
{
    GLUquadric *quadrick = gluNewQuadric();
    gluQuadricDrawStyle(quadrick, GLU_LINE);

    GLfloat lastX=vehicleAttitude.x, lastY=vehicleAttitude.y, lastZ=vehicleAttitude.z;

    for (int i=0;i<planItems.length();i++)
    {
        glPushMatrix();
        glColor3d(1,0,0.7);

        glTranslatef(planItems[i].param5X/ sceneDistanceMultiplier ,planItems[i].param6Y/ sceneDistanceMultiplier ,planItems[i].param7Z/ sceneDistanceMultiplier);
        gluSphere(quadrick, 1.5, 10, 8);

        glPopMatrix();
        int offset = 2;
        textRenderer->renderText((planItems[i].param5X)/ sceneDistanceMultiplier,
                   (planItems[i].param6Y + offset)/ sceneDistanceMultiplier,
                   (planItems[i].param7Z)/ sceneDistanceMultiplier,
                   "Этап " + QString::number(i), Qt::magenta);

        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glColor4f(1.00f, 0.00f, 0.70f, 1.0f);

        glVertex3f(lastX/ sceneDistanceMultiplier,  lastY/ sceneDistanceMultiplier,  lastZ/ sceneDistanceMultiplier);
        glVertex3f(planItems[i].param5X/ sceneDistanceMultiplier,
                   planItems[i].param6Y/ sceneDistanceMultiplier,
                   planItems[i].param7Z/ sceneDistanceMultiplier);

        lastX = planItems[i].param5X;
        lastY = planItems[i].param6Y;
        lastZ = planItems[i].param7Z;
        glEnd();
    }
    gluDeleteQuadric(quadrick);
}

void PlanRoute::init(TextRenderer *textRenderer)
{
    initializeOpenGLFunctions();
    this->textRenderer = textRenderer;
}

void PlanRoute::changePlanRoute(QVector<MissionPlanItem> planItems)
{
    this->planItems = planItems;
}
