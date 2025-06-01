#include <glm/glm.hpp>

#include "camera.h"

void Camera::setPosition(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Camera::setTarget(float x, float y, float z)
{
    this->target = glm::vec3(x, y, z);
}

void Camera::setUp(float x, float y, float z)
{
    this->up = glm::vec3(x, y, z);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(this->position, this->target, this->up);
}
