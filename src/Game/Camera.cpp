#include "Camera.h"
#include <glm/gtx/compatibility.hpp>

Camera::Camera(const std::vector<std::shared_ptr<Util::GameObject>> &children)
    : m_Renderer(std::make_shared<Util::Renderer>(children)) {}

void Camera::AddChild(const std::shared_ptr<Util::GameObject> &child) {
    m_Renderer->AddChild(child);
}

void Camera::AddChildren(
    const std::vector<std::shared_ptr<Util::GameObject>> &children) {
    m_Renderer->AddChildren(children);
}

void Camera::RemoveChild(std::shared_ptr<Util::GameObject> child) {
    m_Renderer->RemoveChild(child);
}

void Camera::Update() {
    if (m_IsAnimating) {
        unsigned long passTimeMs =
            Util::Time::GetElapsedTimeMs() - m_AnimationStartMs;
        if (passTimeMs > m_AnimationDuringTimeMs ||
            m_Position == m_AnimationDestination) {
            m_Position = m_AnimationDestination;
            m_IsAnimating = false;
        }
        else {
            float ratio = (float)passTimeMs / m_AnimationDuringTimeMs;
            glm::vec2 move = m_AnimationDestination - m_Position;
            m_Position += move * ratio;
        }
    }

    m_Renderer->Update(m_Position);
}

void Camera::MoveByTime(const unsigned long &duringTimeMs,
                        const glm::vec2 &destination) {
    if (m_IsAnimating) {
        m_Position = m_AnimationDestination;
        Update();
    }
    m_AnimationStartMs = Util::Time::GetElapsedTimeMs();
    m_AnimationDuringTimeMs = duringTimeMs;
    m_AnimationDestination = destination;
    m_IsAnimating = true;
}
