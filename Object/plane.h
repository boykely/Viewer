#ifndef RIPPLEMESH_H
#define RIPPLEMESH_H

#include "object3d.h"

//A planar grid

class Plane:public Object3d
{
public:
    Plane(QString &_pathVertex,QString &_pathFragment,bool circle=false,int _w=0,int _h=0);
    void Bind() override;
    void Draw() override;

private:
    const static int mGridX;
    const static int mGridZ;
    GLuint mVbo;
    GLuint mEbo;
    GLuint mVao;
    QOpenGLFunctions_4_5_Core *mOpenGLFunctions;
    GLSLShader *mShader;

    bool isCircle;
};

#endif // RIPPLEMESH_H
