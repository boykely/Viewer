#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Object3d
{
public:
    Object3d();
    virtual void Bind(){}
    virtual void Unbind(){}
    virtual void Draw(){}
    int Id;
};

#endif // OBJECT3D_H
