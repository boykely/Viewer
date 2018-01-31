#ifndef PLANE_H
#define PLANE_H

#include <QOpenGLFunctions>
#include "GlShader/GLSLShader.h"
#include "Object/object3d.h"

class plane:public Object3d
{
public:
    plane(QString &_pathVertex,QString &_pathFragment);
    void Bind() override;
    void Draw() override;
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
