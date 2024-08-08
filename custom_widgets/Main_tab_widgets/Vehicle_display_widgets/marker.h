#ifndef MARKER_H
#define MARKER_H

#include <QOpenGLExtraFunctions>
#include <PositionStructs.h>
#include "objloader.h"
#include "textrenderer.h"


class Marker: protected QOpenGLExtraFunctions
{
    TextRenderer *textRenderer;
    GLuint markerModel;
    QVector<QVector<char>> markerMap = {};
    QVector<MarkerInfo> markerInfoVector = {};
public:
    Marker();
    void init(TextRenderer *textRenderer);
    void draw(float sceneDistanceMultiplier);
    void changeMarkerMap(QVector<QVector<char>> markerMap, QVector<MarkerInfo> markerInfoVector);
protected:
    MarkerInfo findMarkerById(int id);
};

#endif // MARKER_H
