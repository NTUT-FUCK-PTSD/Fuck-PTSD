#include "Camera.h"

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
    m_Renderer->Update(m_Position);
}
