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
    float *mColors;
    GLuint mVbo;
    GLuint mVbo2;
    GLuint mVao;
    QOpenGLFunctions_4_5_Core *mOpenGLFunctions;
    GLSLShader *mShader;
};

#endif // TRIANGLE_H
