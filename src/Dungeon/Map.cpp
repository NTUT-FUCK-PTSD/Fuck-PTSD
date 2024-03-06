#include "Dungeon/Map.h"

namespace Dungeon {

Map::Map(const std::string path, const int levelNum) {
    m_Level = std::make_unique<Level>(path, levelNum);
    for (auto &tile : m_Level->GetTiles()) {
        m_Children.push_back(std::make_shared<Tile>(tile));
    }
}

void Map::AddChild(const std::shared_ptr<Util::GameObject> &child) {
    m_Children.push_back(child);
}

void Map::AddChildren(
    const std::vector<std::shared_ptr<Util::GameObject>> &children) {
    m_Children.insert(m_Children.end(), children.begin(), children.end());
}

void Map::RemoveChild(std::shared_ptr<Util::GameObject> child) {
    m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child),
                     m_Children.end());
}

std::vector<std::shared_ptr<Util::GameObject>> Map::GetChildren() {
    return m_Children;
}

} // namespace Dungeon
