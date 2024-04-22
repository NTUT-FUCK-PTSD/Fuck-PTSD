#ifndef GENERALDOORSIDE_H
#define GENERALDOORSIDE_H

#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralDoorSide : public Tile {
public:
    GeneralDoorSide(const s_Tile& u_Tile, const bool generalDoorSide = true);
    virtual ~GeneralDoorSide() override = default;

    bool IsWall() override { return false; };
    bool IsDoor() override { return true; };
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // GENERALDOORSIDE_H
