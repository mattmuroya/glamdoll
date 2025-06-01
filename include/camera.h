#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f); // Camera position
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f); // Target position
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Up vector

public:
    void setPosition(float, float, float);
    void setTarget(float, float, float);
    void setUp(float, float, float);

    glm::mat4 getViewMatrix();
};

#endif
