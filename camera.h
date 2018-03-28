#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <QWheelEvent>
#include <QMouseEvent>

class Camera
{
public:
    Camera(int _width,int _height,glm::vec3 _origin=glm::vec3(0,0,0),glm::vec3 _target=glm::vec3(0));
    glm::vec3 Origin;
    glm::vec3 Direction;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 Target;
    glm::mat4 View;
    glm::mat4 Projection;
    void Zoom(float step);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    float mFov;
    float mPitch;
    float mYaw;
    int mWidth;
    int mHeight;
    bool mMouseLeftPressed = false;
    QPoint mWidgetMousePosition;
};

#endif // CAMERA_H
