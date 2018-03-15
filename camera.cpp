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
    mYaw=15.0f;
    mPitch=15.0f;
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

void Camera::mouseMoveEvent(QMouseEvent *event)
{
    if(mMouseLeftPressed)
    {
        QPoint current=event->pos();
        mWidgetMousePosition-=current;
//        qDebug()<<mWidgetMousePosition;
        float sensitivity=2.0f;
        int x=mWidgetMousePosition.x()<0?1:-1;
        int y=mWidgetMousePosition.y()<0?-1:1;
        float xoffset=x*sensitivity;
        float yoffset=y*sensitivity;
        mYaw+=xoffset;
        mPitch+=yoffset;
//        qDebug()<<mYaw<<"//"<<mPitch;

//        if(mPitch>80.0f)
//            mPitch=80.0f;
//        if(mPitch<-80.0f)
//            mPitch=-80.0f;

        glm::vec3 front;
        float length=glm::length(Target-Origin);
        front.x=sin(glm::radians(mYaw))*length;
        front.y=Origin.y;
        front.z=cos(glm::radians(mYaw))*length;

        glm::vec3 _up=glm::vec3(0,1,0);
        View=glm::lookAt(front,Target,_up);

//        Origin=front;

        mWidgetMousePosition=current;
    }
}

void Camera::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mWidgetMousePosition=event->pos();
        mMouseLeftPressed=true;
    }
}

void Camera::mouseReleaseEvent(QMouseEvent *event)
{
    mMouseLeftPressed=false;
}
void Camera::Zoom(float step)
{
    mFov+=step;
    mFov=mFov<=25.0f?30.0f:(mFov>=160.0f?160.0f:mFov);
    Projection=glm::perspective(glm::radians(mFov),(float)mWidth/mHeight,0.01f,100.0f);
}
