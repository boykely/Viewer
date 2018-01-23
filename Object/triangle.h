#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QOpenGLFunctions>
#include "GlShader/GLSLShader.h"

class Triangle
{
public:
    Triangle();
    void Bind();
    void Draw();
private:
    float *mVertices;
    GLuint mVbo;
    QOpenGLFunctions *mOpenGLFunctions;
    GLSLShader *mShader;
};

#endif // TRIANGLE_H
