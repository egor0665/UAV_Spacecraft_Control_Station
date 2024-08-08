#include "marker.h"


Marker::Marker()
{

}

void Marker::init(TextRenderer *textRenderer)
{
    initializeOpenGLFunctions();
    this->textRenderer = textRenderer;
    markerModel = objLoader::Instance().load("C:/Qt/5.15.2/mingw81_32/GroundControlStation/marker.obj" );
}

void Marker::draw(float sceneDistanceMultiplier)
{
    for (int i=0;i<markerMap.length();i++)
    {
        for (int j=0;j<markerMap.length();j++)
        {
            if ((markerMap[i][j]=='T') || (markerMap[i][j]=='B') || (markerMap[i][j]=='L') || (markerMap[i][j]=='R'))
            {
                MarkerInfo marker1 = findMarkerById(i);
                MarkerInfo marker2 = findMarkerById(j);

                glBegin(GL_LINES);
                glLineWidth(2.0f);
                    glColor4f(0.30f, 0.80f, 0.00f, 1.0f);

                    glVertex3f(marker1.attitude.x/ sceneDistanceMultiplier,
                               marker1.attitude.y/ sceneDistanceMultiplier,
                               marker1.attitude.z/ sceneDistanceMultiplier);
                    glVertex3f(marker2.attitude.x/ sceneDistanceMultiplier,
                               marker2.attitude.y/ sceneDistanceMultiplier,
                               marker2.attitude.z/ sceneDistanceMultiplier);
                glEnd();
            }
        }
    }

    for (int i=0;i<markerInfoVector.length();i++)
    {
        glPushMatrix();

        glTranslatef(markerInfoVector[i].attitude.x/ sceneDistanceMultiplier,
                     markerInfoVector[i].attitude.y/ sceneDistanceMultiplier,
                     markerInfoVector[i].attitude.z/ sceneDistanceMultiplier);

        glRotatef(markerInfoVector[i].attitude.xRot,1,0,0);
        glRotatef(markerInfoVector[i].attitude.yRot,0,1,0);
        glRotatef(markerInfoVector[i].attitude.zRot,0,0,1);

        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glColor4f(0.30f, 0.80f, 0.00f, 1.0f);

            glVertex3f(0,  0,  0);
            glVertex3f(0,  1,  0);

        glEnd();

        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glColor4f(0.20f, 0.20f, 1.00f, 1.0f);

            glVertex3f(0,  0,  0);
            glVertex3f(0,  0,  1);

        glEnd();

        glColor4f(0.30f, 0.80f, 0.00f, 1.0f);
        glCallList(markerModel);
        glPopMatrix();

        int yOffset = 1;
        textRenderer->renderText(markerInfoVector[i].attitude.x / sceneDistanceMultiplier,
                   (markerInfoVector[i].attitude.y + yOffset)/ sceneDistanceMultiplier,
                   markerInfoVector[i].attitude.z / sceneDistanceMultiplier,
                   "М. " + QString::number(markerInfoVector[i].id), Qt::green);
    }
}


MarkerInfo Marker::findMarkerById(int id)
{
    for (int i=0;i<markerInfoVector.length();i++)
    {
        if (markerInfoVector[i].id==id)
        {
            return markerInfoVector[i];
        }
    }
    return MarkerInfo();
}

void Marker::changeMarkerMap(QVector<QVector<char> > markerMap, QVector<MarkerInfo> markerInfoVector)
{
    this->markerMap = markerMap;
    this->markerInfoVector = markerInfoVector;
}
