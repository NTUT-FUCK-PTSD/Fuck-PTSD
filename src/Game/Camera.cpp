#include "Game/Camera.h"

#include <glm/gtc/random.hpp>
#include <glm/gtx/compatibility.hpp>

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
    m_Animation->UpdateAnimation();
    if (m_Animation->IsAnimating()) {
        m_Position = m_Animation->GetAnimationPosition();
    }

    if (m_IsShaking) {
        ShakeUpdate();
    }
    m_Renderer->AddChildren(m_GameChildren);
    m_Renderer->Update(m_Position);
    m_Renderer->ClearChildren();
    m_Renderer->AddChildren(m_UIChildren);
    m_Renderer->Update({0, 0});
    m_Renderer->ClearChildren();
}

void Camera::SetPosition(const glm::vec2 position) {
    if (position == m_Position) {
        return;
    }
    if (m_IsShaking) {
        m_Position = m_OrginalPosition;
        m_ShakeDuringTimeMs = 0;
        m_IsShaking = false;
    }

    m_Animation->MoveByTime(0, position);
}

void Camera::MoveByTime(
    const unsigned long duringTimeMs,
    const glm::vec2&    destination
) {
    if (destination == m_Position) {
        return;
    }
    if (m_IsShaking) {
        m_Position = m_OrginalPosition;
        m_ShakeDuringTimeMs = 0;
        m_IsShaking = false;
    }

    m_Animation->MoveByTime(duringTimeMs, destination);
}

void Camera::Shake(const unsigned long duringTimeMs, const float strength) {
    if (m_Animation->IsAnimating()) {
        m_ShakeHoldDuringTimeMs = m_Animation->GetAnimationDuringTimeMs()
                                  - (Util::Time::GetElapsedTimeMs()
                                     - m_Animation->GetAnimationStartMs());
        m_ShakeHoldDestination = m_Animation->GetAnimationDestination();
        m_ShakeHold = true;
        m_Animation->SetAnimationStop();
    }
    if (m_IsShaking) {
        m_Position = m_OrginalPosition;
        m_ShakeDuringTimeMs = 0;
        m_IsShaking = false;
    }
    m_IsShaking = true;
    m_ShakeStartMs = Util::Time::GetElapsedTimeMs();
    m_ShakeDuringTimeMs = duringTimeMs;
    m_ShakeStrength = strength;
    m_OrginalPosition = m_Position;
    ShakeUpdate();
}

void Camera::ShakeUpdate() {
    if (m_ShakeDuringTimeMs == 0) {
        return;
    }
    unsigned long passTimeMs = Util::Time::GetElapsedTimeMs() - m_ShakeStartMs;
    if (passTimeMs > m_ShakeDuringTimeMs) {
        m_Animation->SetAnimationStop();
        m_Position = m_OrginalPosition;
        m_ShakeDuringTimeMs = 0;
        m_IsShaking = false;
        if (m_ShakeHold) {
            m_Animation->MoveByTime(
                m_ShakeHoldDuringTimeMs,
                m_ShakeHoldDestination
            );
            m_ShakeHold = false;
        }
    } else {
        m_Animation->MoveByTime(
            50,
            glm::linearRand(
                m_OrginalPosition
                    + glm::vec2(-m_ShakeStrength, -m_ShakeStrength),
                m_OrginalPosition + glm::vec2(m_ShakeStrength, m_ShakeStrength)
            )
        );
    }
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
