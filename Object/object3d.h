#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <QOpenGLFunctions>
#include "GlShader/GLSLShader.h"

class Object3d
{
public:
    Object3d();
    Object3d(int _w,int _h);
    virtual void Bind(){}
    virtual void Unbind(){}
    virtual void Draw(){}
    int Id;
    int ScreenWidth;
    int ScreenHeight;
protected:
    QVector<float> mVertices;
    QVector<unsigned int> mIndices;
    QVector<float> mColors;
    QVector<unsigned int> mTexId;
};

#endif // OBJECT3D_H
