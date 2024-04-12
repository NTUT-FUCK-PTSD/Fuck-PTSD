#ifndef GENERALDOORFRONT_H
#define GENERALDOORFRONT_H

#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralDoorFront : public Tile {
public:
    GeneralDoorFront(const s_Tile &u_Tile, const bool generalDoorFront = true);
    GeneralDoorFront(const s_Tile &u_Tile, const std::string &filePath,
                     const bool generalDoorFront = true);
    virtual ~GeneralDoorFront() override = default;

    bool IsWall() override { return false; };
    bool IsDoor() override { return true; };
};
} // namespace Tiles
} // namespace Dungeon

#endif // GENERALDOORFRONT_H
