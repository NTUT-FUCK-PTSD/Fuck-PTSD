#include "Dungeon/Map.h"

namespace Map {

Map::Map(std::string path, int levelNum) {
    m_Level = std::make_unique<Level>(path, levelNum);
}

} // namespace Map
