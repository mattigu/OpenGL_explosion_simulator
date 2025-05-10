#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up) : m_position(position), m_direction(direction),
m_up(up)
{
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = m_movementSpeed * deltaTime;

    switch (direction)
    {
    case CameraMovement::Forward:
        m_position += m_direction * velocity;
        break;
    case CameraMovement::Backward:
        m_position -= m_direction * velocity;
        break;
    case CameraMovement::Left:
        m_position -= glm::normalize(glm::cross(m_direction, m_up)) * velocity;
        break;
    case CameraMovement::Right:
        m_position += glm::normalize(glm::cross(m_direction, m_up)) * velocity;
        break;
    case CameraMovement::Up:
        m_position += m_up * velocity;
        break;
    case CameraMovement::Down:
        m_position -= m_up * velocity;
        break;
    }
}

