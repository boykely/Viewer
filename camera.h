#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 _origin=glm::vec3(0));
    glm::vec3 Origin;
    glm::vec3 Direction;
    glm::vec3 Up;
    glm::vec3 Right;
};

#endif // CAMERA_H
