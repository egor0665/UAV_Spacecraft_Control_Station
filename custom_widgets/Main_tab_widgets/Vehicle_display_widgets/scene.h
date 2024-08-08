#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLExtraFunctions>
#include <PositionStructs.h>
#include "textrenderer.h"

class Scene: protected QOpenGLExtraFunctions
{
    TextRenderer *textRenderer;
    Offset sceneOffset;
    GLfloat totalSceneDist;
//    GLfloat XsceneOffset;
//    GLfloat ZsceneOffset;
//    GLfloat YsceneOffset;
    GLfloat numSceneLines;
    GLfloat sceneUnitDist;
public:
    Scene();
    void init(GLfloat totalSceneDist, Offset sceneOffset, GLfloat numSceneLines, TextRenderer *textRenderer);
    void draw(float sceneDistanceMultiplier);
    const Offset &getSceneOffset() const;
};

#endif // SCENE_H
