#ifndef MAP_H
#define MAP_H

#include "Camera.h"
#include "Dungeon/Level.h"
#include "Dungeon/Tile.h"

namespace Dungeon {

class Map {
public:
    Map(const std::shared_ptr<Camera> &camera, const std::string &path,
        const int &levelNum = 1);

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

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    void SetVisible(const bool &visible);

    void Update();

private:
    bool m_Visible = true;
    std::unique_ptr<Level> m_Level;
    glm::ivec2 m_Size;
    std::vector<std::vector<std::shared_ptr<Tile>>>
        m_Tiles; // Use map index to store tiles
    std::vector<std::shared_ptr<Util::GameObject>> m_Children;
    std::shared_ptr<Camera> m_Camera;
};

} // namespace Dungeon
#endif // MAP_H
