#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <algorithm>
#include <iostream>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

class Camera
{
public:
    Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Forward = glm::vec3(0.0f, 0.0f, 1.0f))
        : m_Position(Position), m_Forward(Forward)
    {
        m_Pitch = glm::degrees(asin(m_Forward.y));
        m_Yaw = glm::degrees(atan2(m_Forward.z, m_Forward.x));
        std::cout << m_Pitch << " " << m_Yaw << std::endl;
        UpdateCameraVectors();
        UpdatePerspectiveProjectionMatrix(1920, 1080);
    }

    [[nodiscard]] const glm::mat4& GetViewMatrix() const
    {
        return m_ViewMat;
    }

    [[nodiscard]] const glm::mat4& GetPerspectiveProjectionMatrix() const
    {
        return m_PerspectiveProjMat;
    }

    void UpdatePerspectiveProjectionMatrix(const uint32_t Width, const uint32_t Height)
    {
        m_PerspectiveProjMat = glm::perspective(glm::radians(m_FOV), static_cast<float>(Width) / Height,
                                                m_NearClipPlane, m_FarClipPlane);
    }

    void ProcessKeyboard(const CameraMovement Direction, const float DeltaTime)
    {
        const float velocity = m_MovementSpeed * DeltaTime;
        if (Direction == CameraMovement::FORWARD)
            m_Position += m_Forward * velocity;
        if (Direction == CameraMovement::BACKWARD)
            m_Position -= m_Forward * velocity;
        if (Direction == CameraMovement::LEFT)
            m_Position -= m_Right * velocity;
        if (Direction == CameraMovement::RIGHT)
            m_Position += m_Right * velocity;
        if (Direction == CameraMovement::UP)
            m_Position += m_Up * velocity;
        if (Direction == CameraMovement::DOWN)
            m_Position -= m_Up * velocity;
    }

    void ProcessMouseMovement(const float OffsetX, const float OffsetY)
    {
        m_Yaw += OffsetX * m_MouseSensitivity;
        m_Pitch += OffsetY * m_MouseSensitivity;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        m_Pitch = std::clamp(m_Pitch, -89.0f, 89.0f);

        // update Front, Right and Up Vectors using the updated Euler angles
        UpdateCameraVectors();
    }

private:
    void UpdateCameraVectors()
    {
        const float pitchRadians = glm::radians(m_Pitch);
        const float yawRadians = glm::radians(m_Yaw);
        const float cosPitch = cos(pitchRadians);

        const auto forward = glm::vec3(cos(yawRadians) * cosPitch, sin(pitchRadians), sin(yawRadians) * cosPitch);
        m_Forward = glm::normalize(forward);
        m_Right = glm::normalize(glm::cross(m_Forward, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
        m_ViewMat = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
    }

private:
    glm::vec3 m_Position;
    glm::vec3 m_Forward;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp{glm::vec3(0.0f, 1.0f, 0.0f)};

    float m_Yaw;
    float m_Pitch;
    float m_MovementSpeed{2.5f};
    float m_MouseSensitivity{0.1f};
    float m_FOV{60.0f};
    float m_NearClipPlane{0.1f};
    float m_FarClipPlane{100.0f};

    glm::mat4 m_ViewMat;
    glm::mat4 m_PerspectiveProjMat;
};
