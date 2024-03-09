#ifndef MAP_H
#define MAP_H

#include "Dungeon/Level.h"
#include "Dungeon/Tile.h"

namespace Dungeon {

class Map {
public:
    Map(const std::string &path, const int levelNum = 1);

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

private:
    std::unique_ptr<Level> m_Level;
    std::vector<std::shared_ptr<Util::GameObject>> m_Children;
};

} // namespace Dungeon
#endif // MAP_H
