#ifndef OBJECT3D_H
#define OBJECT3D_H


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
