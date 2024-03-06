#ifndef MAP_H
#define MAP_H

#include "Dungeon/Level.h"

#include <memory>

namespace Dungeon {

class Map {
public:
    Map(std::string path, int levelNum = 1);

private:
    std::unique_ptr<Level> m_Level;
};

} // namespace Dungeon
#endif // MAP_H
