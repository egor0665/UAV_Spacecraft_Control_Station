#include "helplines.h"

HelpLines::HelpLines()
{

}

void HelpLines::init(TextRenderer *textRenderer)
{
    initializeOpenGLFunctions();
    this->textRenderer = textRenderer;
}

void HelpLines::draw(Offset sceneOffset, AttitudeInfo vehicleAttitude, float sceneDistanceMultiplier)
{

    glColor4f(1.00f, 1.00f, 1.00f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
        glColor4f(1.00f, 1.00f, 0.00f, 1.0f);

        glVertex3f(vehicleAttitude.x / sceneDistanceMultiplier,  vehicleAttitude.y / sceneDistanceMultiplier,  vehicleAttitude.z / sceneDistanceMultiplier);
        glVertex3f(vehicleAttitude.x / sceneDistanceMultiplier,  (0 + sceneOffset.yOffset) ,  vehicleAttitude.z / sceneDistanceMultiplier);

        glVertex3f(vehicleAttitude.x / sceneDistanceMultiplier,  vehicleAttitude.y / sceneDistanceMultiplier,  vehicleAttitude.z / sceneDistanceMultiplier);
        glVertex3f((0 + sceneOffset.xOffset) ,  vehicleAttitude.y/ sceneDistanceMultiplier,  vehicleAttitude.z / sceneDistanceMultiplier );

        glVertex3f(vehicleAttitude.x / sceneDistanceMultiplier,  vehicleAttitude.y / sceneDistanceMultiplier,  vehicleAttitude.z / sceneDistanceMultiplier);
        glVertex3f(vehicleAttitude.x / sceneDistanceMultiplier,  vehicleAttitude.y / sceneDistanceMultiplier,  (0 + sceneOffset.zOffset) );

    glEnd();

    textRenderer->renderText(vehicleAttitude.x / sceneDistanceMultiplier ,  (0 + sceneOffset.yOffset) ,  vehicleAttitude.z / sceneDistanceMultiplier, "( " + QString::number(vehicleAttitude.x,'f',2) + "," + QString::number(vehicleAttitude.z,'f',2) + " )", Qt::yellow);
    textRenderer->renderText((0 + sceneOffset.xOffset),  vehicleAttitude.y  / sceneDistanceMultiplier,  vehicleAttitude.z  / sceneDistanceMultiplier, "( " + QString::number(vehicleAttitude.y,'f',2) + "," + QString::number(vehicleAttitude.z,'f',2) + " )", Qt::yellow);
    textRenderer->renderText(vehicleAttitude.x / sceneDistanceMultiplier,  vehicleAttitude.y / sceneDistanceMultiplier,  (0 + sceneOffset.zOffset), "( " + QString::number(vehicleAttitude.x,'f',2) + "," + QString::number(vehicleAttitude.y,'f',2) + " )", Qt::yellow);

}
