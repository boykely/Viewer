#ifndef RIPPLEMESH_H
#define RIPPLEMESH_H

#include <QOpenGLFunctions>
#include "object3d.h"
#include "GlShader/GLSLShader.h"

//A planar grid

class RippleMesh:public Object3d
{
public:
    RippleMesh(QString &_pathVertex,QString &_pathFragment);
    void Bind() override;
    void Draw() override;

private:
    const static int mGridX;
    const static int mGridZ;
    float *mVertices;
    unsigned int *mIndices;
    GLuint mVbo;
    GLuint mEbo;
    GLuint mVao;
    QOpenGLFunctions_4_5_Core *mOpenGLFunctions;
    GLSLShader *mShader;
};

#endif // RIPPLEMESH_H
