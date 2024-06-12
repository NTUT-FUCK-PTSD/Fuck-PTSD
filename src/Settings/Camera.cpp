#include "Settings/Camera.h"

#include "glm/gtc/random.hpp"

#include "Util/Time.hpp"

Camera::Camera(const std::vector<std::shared_ptr<Util::GameObject>>& children)
    : m_Renderer(std::make_unique<Util::Renderer>(children)) {
    m_Animation = std::make_unique<Animation>(GetPosition());
}

void Camera::AddChild(const std::shared_ptr<Util::GameObject> child) {
    m_GameChildren.push_back(child);
}

void Camera::AddChildren(
    const std::vector<std::shared_ptr<Util::GameObject>>& children
) {
    m_GameChildren.reserve(m_GameChildren.size() + children.size());
    m_GameChildren
        .insert(m_GameChildren.end(), children.begin(), children.end());
}

void Camera::RemoveChild(std::shared_ptr<Util::GameObject> child) {
    m_GameChildren.erase(
        std::remove(m_GameChildren.begin(), m_GameChildren.end(), child),
        m_GameChildren.end()
    );
}

void Camera::Update() {
    auto elapsedTimeMs = Util::Time::GetElapsedTimeMs();
    auto randomShake = glm::vec2(0, 0);
    if (m_ShakeStartMs + m_ShakeDuringTimeMs > elapsedTimeMs) {
        randomShake = glm::vec2(
            glm::linearRand(-m_ShakeStrength, m_ShakeStrength),
            glm::linearRand(-m_ShakeStrength, m_ShakeStrength)
        );
    }
    if (m_Animation->UpdateAnimation()) {
        m_Position = m_Animation->GetAnimationPosition();
    }
    m_Renderer->AddChildren(m_GameChildren);
    m_Renderer->Update(m_Position + randomShake);
    m_Renderer->ClearChildren();
    m_Renderer->AddChildren(m_UIChildren);
    m_Renderer->Update({0, 0});
    m_Renderer->ClearChildren();
}

void Camera::SetPosition(const glm::vec2 position) {
    if (position == m_Position) { return; }
    m_Animation->UpdateGamePosition(position);
    m_Position = position;
}

void Camera::MoveByTime(
    const unsigned long duringTimeMs,
    const glm::vec2&    destination
) {
    m_Animation->MoveByTime(duringTimeMs, destination);
}

void Camera::Shake(const unsigned long duringTimeMs, const float strength) {
    m_ShakeStartMs = Util::Time::GetElapsedTimeMs();
    m_ShakeDuringTimeMs = duringTimeMs;
    m_ShakeStrength = strength;
}

void Camera::AddUIChild(const std::shared_ptr<Util::GameObject> child) {
    m_UIChildren.push_back(child);
}

void Camera::AddUIChildren(
    const std::vector<std::shared_ptr<Util::GameObject>>& children
) {
    m_UIChildren.reserve(m_UIChildren.size() + children.size());
    m_UIChildren.insert(m_UIChildren.end(), children.begin(), children.end());
}

void Camera::RemoveUIChild(std::shared_ptr<Util::GameObject> child) {
    m_UIChildren.erase(
        std::remove(m_UIChildren.begin(), m_UIChildren.end(), child),
        m_UIChildren.end()
    );
}
