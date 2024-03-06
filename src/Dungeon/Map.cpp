#include "Dungeon/Map.h"

namespace Dungeon {

Map::Map(const std::string path, const int levelNum) {
    m_Level = std::make_unique<Level>(path, levelNum);
}

} // namespace Dungeon
