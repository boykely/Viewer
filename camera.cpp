#include "camera.h"

Camera::Camera(glm::vec3 _origin,glm::vec3 _target):Origin(_origin),Target(_target)
{
    Direction=glm::normalize(Origin-Target);
    glm::vec3 _up=glm::vec3(0,1,0);
    Right=glm::normalize(glm::cross(_up,Direction));
    Up=glm::cross(Right,Direction);
    //To construct own View matrix from Righ,Up,Direction
    //Visit learnopengl.com/Getting-started/Camera
    View=glm::lookAt(Origin,Target,_up);
}
