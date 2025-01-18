#include "camera.h"


Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch)
: position(startPosition), front(glm::vec3(0.0f, 0.0f, -1.0f)),xfront(glm::vec3(0.0f, 0.0f, -1.0f)), up(startUp), yaw(startYaw), pitch(startPitch), movementSpeed(2.5f) {}

void Camera::ProcessKeyboard(int direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime; 
    if(direction == GLFW_KEY_W&&position.x>=-10.0f&&position.x<=10.0f&&position.z>=-10.0f&&position.z<=10.0f) position += xfront * velocity; 
    else if(direction == GLFW_KEY_W) position -= xfront * velocity*2.0f; 

    if(direction == GLFW_KEY_S&&position.x>=-10.0f&&position.x<=10.0f&&position.z>=-10.0f&&position.z<=10.0f) position -= xfront * velocity; 
    else if(direction == GLFW_KEY_S) position += xfront * velocity*2.0f; 
    
    if(direction == GLFW_KEY_A&&position.x>=-10.0f&&position.x<=10.0f&&position.z>=-10.0f&&position.z<=10.0f) position -= glm::normalize(glm::cross(xfront, up)) * velocity; 
    else if(direction == GLFW_KEY_A) position += glm::normalize(glm::cross(xfront, up)) * velocity*2.0f;
    
    if(direction == GLFW_KEY_D&&position.x>=-10.0f&&position.x<=10.0f&&position.z>=-10.0f&&position.z<=10.0f) position += glm::normalize(glm::cross(xfront, up)) * velocity;
    else if(direction == GLFW_KEY_D) position -= glm::normalize(glm::cross(xfront, up)) * velocity*2.0f;

}
//&&position.x>-10.0f&&position.x<10.0f&&position.y>-10.0f&&position.y<10.0f
glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if(constrainPitch) {
        if(pitch > 89.0f) pitch = 89.0f; 
        if(pitch < -89.0f) pitch = -89.0f; 
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
  
    glm::vec3 xfront;
    xfront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  //  xfront.y = sin(glm::radians(pitch));
    xfront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->xfront = glm::normalize(xfront);
}
