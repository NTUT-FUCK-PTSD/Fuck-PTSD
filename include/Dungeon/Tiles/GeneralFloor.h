#ifndef GENERALFLOOR_H
#define GENERALFLOOR_H

#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralFloor : public Tile {
public:
    explicit GeneralFloor(const s_Tile& _Tile, const bool generalFloor = true);
    virtual ~GeneralFloor() override = default;

    bool IsWall() override { return false; };
    bool IsDoor() override { return false; };
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // GENERALFLOOR_H
