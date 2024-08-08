#include "startpoint.h"

StartPoint::StartPoint()
{

}

void StartPoint::init(AttitudeInfo attitude, TextRenderer *textRenderer)
{
    initializeOpenGLFunctions();
    this->attitude = attitude;
    this->textRenderer = textRenderer;
}

void StartPoint::draw(float sceneDistanceMultiplier)
{
    glLineWidth(2.0f);
     glBegin(GL_LINES);
     glColor4f(1.00f, 1.00f, 0.00f, 1.0f);

     glVertex3f(attitude.x / sceneDistanceMultiplier-1,  attitude.y/ sceneDistanceMultiplier,  attitude.z/ sceneDistanceMultiplier-1);
     glVertex3f(attitude.x/ sceneDistanceMultiplier+1,  attitude.y/ sceneDistanceMultiplier,  attitude.z/ sceneDistanceMultiplier+1);

     glVertex3f(attitude.x/ sceneDistanceMultiplier-1, attitude.y/ sceneDistanceMultiplier,  attitude.z/ sceneDistanceMultiplier+1);
     glVertex3f(attitude.x/ sceneDistanceMultiplier+1, attitude.y/ sceneDistanceMultiplier,  attitude.z/ sceneDistanceMultiplier-1);

     glEnd();
}

void StartPoint::changeAttitude(AttitudeInfo newAttitude)
{
    this->attitude = newAttitude;
}
