#ifndef CUBE_H
#define CUBE_H

#include "object3d.h"

class Cube: public Object3d
{
public:
    Cube(QString &_pathVertex,QString &_pathFragment,int w=0,int h=0);
    void Bind() override;
    void Draw() override;
private:

    GLuint mVbo;
    GLuint mVboColor;
    GLuint mVao;
    GLuint mEbo;
    QOpenGLFunctions_4_5_Core *mOpenGLFunctions;
    GLSLShader *mShader;
};

#endif // CUBE_H
