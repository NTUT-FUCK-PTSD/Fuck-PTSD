#ifndef CAMERA_H
#define CAMERA_H

#include "Util/Renderer.hpp"

class Camera {
public:
    /**
     * @brief Parameterized constructor.
     *`
     *
     * @param children The GameObject needing to be managed by Renderer.
     */
    Camera(const std::vector<std::shared_ptr<Util::GameObject>> &children = {});

    /**
     * @brief Add a child to Renderer.
     *
     * @param child The GameObject needing to be managed by Renderer.
     */
    void AddChild(const std::shared_ptr<Util::GameObject> &child);

    /**
     * @brief Add children to Renderer.
     *
     * @param children The GameObjects needing to be managed by Renderer.
     */
    void
    AddChildren(const std::vector<std::shared_ptr<Util::GameObject>> &children);

    /**
     * @brief Remove the child.
     *
     * @param child The GameObject being removed.
     */
    void RemoveChild(std::shared_ptr<Util::GameObject> child);

    /**
     * @brief Draw children according to their z-index.
     *
     * @note The user is not recommended to modify this function.
     */
    void Update();

    void SetPosition(const glm::vec2 &position) { m_Position = position; }

    glm::vec2 GetPosition() { return m_Position; }

    std::shared_ptr<Util::Renderer> GetRenderer() { return m_Renderer; }

private:
    std::shared_ptr<Util::Renderer> m_Renderer;
    glm::vec2 m_Position = {0, 0};
};

#endif // CAMERA_H
