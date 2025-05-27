#include <glm/glm.hpp>

#include "camera.h"

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(this->position, this->target, this->up);
}
