#include "camera.h"

#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch) : 
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), Position(position), WorldUp(worldUp), Yaw(yaw), Pitch(pitch), Fov(_FOV), CameraSpeed(_CAMERA_SPEED), MouseSensitivity(_MOUSE_SENS) 
{
    updateCameraVectors();      
}

glm::mat4 Camera::getLookAt(){
    return glm::lookAt(Position, Position + Front,  Up);
}

void Camera::processKeyboard(float deltaTime) {
    float cameraSpeedDelta = CameraSpeed * deltaTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)){
        Position += cameraSpeedDelta * Front;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)){
        Position -= cameraSpeedDelta * Front;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
        Position -= Right * cameraSpeedDelta;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
        Position += Right * cameraSpeedDelta;
    }
}

void Camera::processMouse(float windowWidth, float windowHeight, float xpos, float ypos) {
    float centreX = windowWidth/2.0f; 
    float centreY = windowHeight/2.0f;

    float xoffset = xpos - centreX;
    float yoffset = centreY - ypos; // reversed

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front; 
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}