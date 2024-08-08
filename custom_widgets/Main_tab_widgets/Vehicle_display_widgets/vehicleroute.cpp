#include "vehicleroute.h"

VehicleRoute::VehicleRoute()
{
    routeVector.clear();
}

void VehicleRoute::init(TextRenderer *textRenderer)
{
    initializeOpenGLFunctions();
    this->textRenderer = textRenderer;
}

void VehicleRoute::draw(float sceneDistanceMultiplier)
{
    GLfloat lastX=0, lastY=0, lastZ=0;
    if (!routeVector.isEmpty())
        lastX=routeVector[0].x, lastY=routeVector[0].y, lastZ=routeVector[0].z;
    glLineWidth(2.0f);
     glBegin(GL_LINES);
     glColor4f(0.00f, 1.00f, 1.00f, 1.0f);
    for (int i=1;i<routeVector.length();i++)
    {
        glVertex3f(lastX/ sceneDistanceMultiplier,  lastY/ sceneDistanceMultiplier,  lastZ/ sceneDistanceMultiplier);
        glVertex3f(routeVector[i].x/ sceneDistanceMultiplier,  routeVector[i].y/ sceneDistanceMultiplier,  routeVector[i].z/ sceneDistanceMultiplier);
        lastX = routeVector[i].x;
        lastY = routeVector[i].y;
        lastZ = routeVector[i].z;
    }
    glEnd();
}

void VehicleRoute::addRoutePoint(PositionInfo position)
{
    routeVector.append(PositionInfo(position.x,position.y,position.z));
    if (routeVector.length()>100)
        routeVector.remove(0);
}
