#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object/object3d.h"

class Triangle:public Object3d
{
public:
    Triangle(QString &_pathVertex,QString &_pathFragment);
    void Bind() override;
    void Draw() override;
private:
    GLuint mVbo;
    GLuint mVbo2;
    GLuint mVao;
    QOpenGLFunctions_4_5_Core *mOpenGLFunctions;
    GLSLShader *mShader;
};

#endif // TRIANGLE_H
