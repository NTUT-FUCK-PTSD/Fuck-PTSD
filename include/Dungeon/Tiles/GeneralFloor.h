#ifndef GENERALFLOOR_HPP
#define GENERALFLOOR_HPP

#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralFloor : public Tile {
public:
    explicit GeneralFloor(const s_Tile &u_Tile);
    virtual ~GeneralFloor() override = default;

    bool IsWall() override { return false; };
    bool IsDoor() override { return false; };
};
} // namespace Tiles
} // namespace Dungeon

#endif // GENERALFLOOR_HPP
