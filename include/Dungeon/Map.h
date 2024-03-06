#ifndef MAP_H
#define MAP_H

#include "Dungeon/Level.h"

#include <memory>

namespace Map {

class Map {
public:
    Map(std::string path, int levelNum = 0);

private:
    std::unique_ptr<Level> m_Level;
};

} // namespace Map
#endif // MAP_H
