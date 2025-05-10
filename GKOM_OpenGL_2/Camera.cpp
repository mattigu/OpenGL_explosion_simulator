#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up) : m_position(position), m_direction(direction),
m_up(up)
{
    m_horizontalAngle = glm::degrees(atan2(direction.z, direction.x));
    m_verticalAngle = glm::degrees(asin(direction.y));
    updateCameraDirection();
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

void Camera::processMouseMovement(float xOffset, float yOffset)
{
    xOffset *= m_mouseSensitivity;
    yOffset *= m_mouseSensitivity;

    m_horizontalAngle += xOffset;
    m_verticalAngle += yOffset;


    if (m_verticalAngle > 89.0f) m_verticalAngle = 89.0f;

    updateCameraDirection();
}

void Camera::updateCameraDirection()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_horizontalAngle)) * cos(glm::radians(m_verticalAngle));
    direction.y = sin(glm::radians(m_verticalAngle));
    direction.z = sin(glm::radians(m_horizontalAngle)) * cos(glm::radians(m_verticalAngle));
    m_direction = glm::normalize(direction);
}

