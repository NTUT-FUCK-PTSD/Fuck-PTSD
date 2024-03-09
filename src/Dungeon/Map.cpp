#include "Dungeon/Map.h"

namespace Dungeon {

Map::Map(const std::string &path, const int levelNum) {
    m_Level = std::make_unique<Level>(path, levelNum);
    for (auto &tile : m_Level->GetTiles()) {
        m_Children.push_back(std::make_shared<Tile>(tile));
        if (tile.type == 103 || tile.type == 106 || tile.type == 111 ||
            tile.type == 118) {
            m_Children.push_back(std::make_shared<Tile>(s_Tile{
                tile.x, tile.y, 0, tile.zone, tile.torch, tile.cracked}));
        }
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
