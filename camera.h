#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(glm::vec3 _origin=glm::vec3(0,0,10),glm::vec3 _target=glm::vec3(0));
    glm::vec3 Origin;
    glm::vec3 Direction;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 Target;
    glm::mat4 View;
    glm::mat4 Projection;
};

#endif // CAMERA_H
