#ifndef GENERALDOOR_HPP
#define GENERALDOOR_HPP

#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralDoor : public Tile {
public:
    explicit GeneralDoor(const s_Tile &u_Tile);
    virtual ~GeneralDoor() override = default;

    bool IsWall() override { return false; };
    bool IsDoor() override { return true; };
};
} // namespace Tiles
} // namespace Dungeon

#endif // GENERALWALL_HPP
