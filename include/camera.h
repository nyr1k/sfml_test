#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SFML/Window.hpp>

#include <glm/gtc/type_ptr.hpp>

const float _YAW   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
const float _PITCH =  0.0f;
const float _FOV   =  45.0f;

const float _CAMERA_SPEED = 2.5f;
const float _MOUSE_SENS = 0.01; 

class Camera {
    public:

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right; 

    glm::vec3 WorldUp;

    float CameraSpeed; 
    float MouseSensitivity;

    float Yaw;
    float Pitch;
    float Fov;

    Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch);
    glm::mat4 getLookAt();
    void processKeyboard(float deltaTime);
    void processMouse(float windowWidth, float windowHeight, float xpos, float ypos);
    
    private:
    void updateCameraVectors();
};

#endif
