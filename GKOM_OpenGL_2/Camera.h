#pragma once
#include <glm/glm.hpp>

enum class CameraMovement {
    Forward, Backward, Left, Right, Up, Down
};

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up);

    void processKeyboard(CameraMovement direction, float deltaTime=1);

    void processMouseMovement(float xOffset, float yOffset);

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getDirection() const { return m_direction; }
    glm::vec3 getUp() const { return m_up; }

private:
    void updateCameraDirection();

    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;

    float m_horizontalAngle;
    float m_verticalAngle;

    float m_movementSpeed = 0.05f;
    float m_mouseSensitivity = 0.1f;
};
