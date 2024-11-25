#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float movementSpeed;
    float yaw;
    float pitch;
    float sensitivity = 0.1f;

    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);

    void ProcessKeyboard(int direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    glm::mat4 GetViewMatrix();
private:
    void updateCameraVectors();
};

#endif // CAMERA_H
