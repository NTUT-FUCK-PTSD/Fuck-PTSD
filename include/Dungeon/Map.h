#ifndef MAP_H
#define MAP_H

#include "Dungeon/Level.h"

#include <memory>

namespace Dungeon {

class Map {
public:
    Map(const std::string path, const int levelNum = 1);

private:
    std::unique_ptr<Level> m_Level;
};

} // namespace Dungeon
#endif // MAP_H
