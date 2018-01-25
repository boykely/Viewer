#ifndef PLANE_H
#define PLANE_H

#include <QOpenGLFunctions>
#include "GlShader/GLSLShader.h"

class plane
{
public:
    plane(QString &_pathVertex,QString &_pathFragment);
    void Bind();
    void Draw();
private:
    float *mVertices;
    float *mColors;
    unsigned int *mIndices;
    GLuint mVbo;
    GLuint mVbo2;
    GLuint mEbo;
    GLuint mVao;
    QOpenGLFunctions_4_5_Core *mOpenGLFunctions;
    GLSLShader *mShader;
};

#endif // PLANE_H
