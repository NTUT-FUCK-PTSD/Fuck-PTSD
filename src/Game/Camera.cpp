#include "Camera.h"

Camera::Camera(const std::vector<std::shared_ptr<Util::GameObject>> &children)
    : m_Renderer(std::make_shared<Util::Renderer>(children)) {
    m_Children = children;
}

void Camera::AddChild(const std::shared_ptr<Util::GameObject> &child) {
    m_Renderer->AddChild(child);
    m_Children.push_back(child);
}

void Camera::AddChildren(
    const std::vector<std::shared_ptr<Util::GameObject>> &children) {
    m_Children.reserve(m_Children.size() + children.size());
    m_Children.insert(m_Children.end(), children.begin(), children.end());
    m_Renderer->AddChildren(children);
}

void Camera::RemoveChild(std::shared_ptr<Util::GameObject> child) {
    m_Renderer->RemoveChild(child);
    m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child),
                     m_Children.end());
}

void Camera::Update() {
    for (auto &child : m_Children) {
        child->m_Transform.translation =
            child->m_Transform.translation + m_Position;
        for (auto &grandchild : child->GetChildren()) {
            grandchild->m_Transform.translation =
                grandchild->m_Transform.translation + m_Position;
        }
    }

    m_Renderer->Update();

    for (auto &child : m_Children) {
        child->m_Transform.translation =
            child->m_Transform.translation - m_Position;
        for (auto &grandchild : child->GetChildren()) {
            grandchild->m_Transform.translation =
                grandchild->m_Transform.translation - m_Position;
        }
    }
}
