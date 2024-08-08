#include "scene.h"

const Offset &Scene::getSceneOffset() const
{
    return sceneOffset;
}

Scene::Scene()
{

}

void Scene::init(GLfloat totalSceneDist, Offset sceneOffset, GLfloat numSceneLines, TextRenderer *textRenderer)
{
    initializeOpenGLFunctions();
    this->totalSceneDist = totalSceneDist;
    this->sceneOffset = sceneOffset;
    this->numSceneLines = numSceneLines;
    this->sceneUnitDist = totalSceneDist/ numSceneLines;
    this->textRenderer = textRenderer;
}

void Scene::draw(float sceneDistanceMultiplier)
{
    glLineWidth(5.0f);
    glBegin(GL_LINES); // построение линии
        glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
        glVertex3f( totalSceneDist + sceneOffset.xOffset,  sceneOffset.yOffset,  sceneOffset.zOffset);
        glVertex3f( sceneOffset.xOffset,  sceneOffset.yOffset,  sceneOffset.zOffset);


        glColor4f(0.00f, 1.00f, 0.00f, 1.0f);
        // ось y зеленого цвета
        glVertex3f( sceneOffset.xOffset,  totalSceneDist + sceneOffset.yOffset,  sceneOffset.zOffset);
        glVertex3f( sceneOffset.xOffset,  sceneOffset.yOffset, sceneOffset.zOffset);


        glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
        // ось z синего цвета
        glVertex3f( sceneOffset.xOffset,  sceneOffset.yOffset,  totalSceneDist+  sceneOffset.zOffset);
        glVertex3f( sceneOffset.xOffset,  sceneOffset.yOffset,  sceneOffset.zOffset);

        glEnd();

        GLfloat offset = 15;
        textRenderer->renderText(totalSceneDist + sceneOffset.xOffset + offset,  sceneOffset.yOffset , sceneOffset.zOffset, "X", Qt::red);
        textRenderer->renderText(sceneOffset.xOffset ,  totalSceneDist + sceneOffset.yOffset  + offset, sceneOffset.zOffset, "Y", Qt::green);
        textRenderer->renderText(sceneOffset.xOffset ,  sceneOffset.yOffset , totalSceneDist + sceneOffset.zOffset + offset, "Z", Qt::blue);


        glLineWidth(0.1f);
        glBegin(GL_LINES);
        glColor4f(1.00f, 1.00f, 1.00f, 1.0f);

        for (int i=1;i<numSceneLines+1;i++)
        {
            glVertex3f( totalSceneDist + sceneOffset.xOffset,  i*sceneUnitDist + sceneOffset.yOffset,  sceneOffset.zOffset);
            glVertex3f( sceneOffset.xOffset,  i*sceneUnitDist + sceneOffset.yOffset, sceneOffset.zOffset);

            glVertex3f( totalSceneDist + sceneOffset.xOffset,  sceneOffset.yOffset,  i*sceneUnitDist + sceneOffset.zOffset);
            glVertex3f( sceneOffset.xOffset,  sceneOffset.yOffset,  i*sceneUnitDist + sceneOffset.zOffset);

            glVertex3f( i*sceneUnitDist + sceneOffset.xOffset,  totalSceneDist + sceneOffset.yOffset,  sceneOffset.zOffset);
            glVertex3f( i*sceneUnitDist + sceneOffset.xOffset,  sceneOffset.yOffset,  sceneOffset.zOffset);

            glVertex3f( sceneOffset.xOffset,  totalSceneDist + sceneOffset.yOffset,  i*sceneUnitDist+sceneOffset.zOffset);
            glVertex3f( sceneOffset.xOffset,  sceneOffset.yOffset,  i*sceneUnitDist+sceneOffset.zOffset);

            glVertex3f( i*sceneUnitDist+sceneOffset.xOffset ,  sceneOffset.yOffset,  totalSceneDist+sceneOffset.zOffset);
            glVertex3f( i*sceneUnitDist+sceneOffset.xOffset,  sceneOffset.yOffset,  sceneOffset.zOffset);

            glVertex3f( sceneOffset.xOffset,  i*sceneUnitDist + sceneOffset.yOffset, totalSceneDist+sceneOffset.zOffset);
            glVertex3f( sceneOffset.xOffset,  i*sceneUnitDist + sceneOffset.yOffset,  sceneOffset.zOffset);
        }
    glEnd();

//    renderText
    textRenderer->renderText(sceneOffset.xOffset ,  sceneOffset.yOffset ,  sceneOffset.zOffset, "( " + QString::number(sceneOffset.xOffset* sceneDistanceMultiplier,'f',2) + "," + QString::number(sceneOffset.zOffset* sceneDistanceMultiplier,'f',2) + " )", Qt::white);
    textRenderer->renderText(sceneOffset.xOffset ,  sceneOffset.yOffset ,  totalSceneDist+sceneOffset.zOffset, "( " + QString::number((totalSceneDist+sceneOffset.xOffset)* sceneDistanceMultiplier,'f',2) + "," + QString::number(0) + " )", Qt::blue);
    textRenderer->renderText(totalSceneDist+sceneOffset.xOffset ,  sceneOffset.yOffset ,  sceneOffset.zOffset, "( " + QString::number(0) + "," + QString::number((totalSceneDist+sceneOffset.zOffset)* sceneDistanceMultiplier,'f',2) + " )", Qt::red);
    textRenderer->renderText(sceneOffset.xOffset ,  totalSceneDist + sceneOffset.yOffset,  sceneOffset.zOffset, "( " + QString::number((totalSceneDist+sceneOffset.xOffset)* sceneDistanceMultiplier,'f',2) + "," + QString::number(0) + " )", Qt::green);
}
