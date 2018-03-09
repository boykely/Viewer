#include "camera.h"
#include <QDebug>

Camera::Camera(int _width,int _height,glm::vec3 _origin,glm::vec3 _target):Origin(_origin),Target(_target),
    mWidth(_width),mHeight(_height)
{
    Direction=glm::normalize(Origin-Target);
    glm::vec3 _up=glm::vec3(0,1,0);
    Right=glm::normalize(glm::cross(_up,Direction));
    Up=glm::cross(Right,Direction);
    //To construct own View matrix from Righ,Up,Direction
    //Visit learnopengl.com/Getting-started/Camera
    View=glm::lookAt(Origin,Target,_up);
    mFov=45.0f;
    Projection=glm::perspective(glm::radians(mFov),(float)mWidth/mHeight,0.01f,100.0f);
}

void Camera::wheelEvent(QWheelEvent *event)
{
    if(event->delta()<0)
    {
        //Zoom out
        Zoom(-5.0f);
    }
    else
    {
        //Zoom in
        Zoom(5.0f);
    }
}

void Camera::Zoom(float step)
{
    mFov+=step;
    mFov=mFov<=25.0f?30.0f:(mFov>=160.0f?160.0f:mFov);
    Projection=glm::perspective(glm::radians(mFov),(float)mWidth/mHeight,0.01f,100.0f);
}
