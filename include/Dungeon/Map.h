#ifndef MAP_H
#define MAP_H

#include "Util/GameObject.hpp"

#include "Camera.h"
#include "Dungeon/Enemy.h"
#include "Dungeon/Level.h"
#include "Dungeon/Tile.h"

namespace Dungeon {
struct s_MapDate {
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
};

class Map : public Util::GameObject {
public:
    Map(const std::string &path, const int &levelNum = 1);

    void TempoUpdate();

private:
    std::unique_ptr<Level> m_Level;
    glm::ivec2 m_Size;
    std::vector<s_MapDate> m_MapData; // Use map index to store MapDate
    std::vector<std::shared_ptr<Tile>> m_Tiles;
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
};

} // namespace Dungeon
#endif // MAP_H
