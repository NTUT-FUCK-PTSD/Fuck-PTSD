#ifndef GENERALWALL_HPP
#define GENERALWALL_HPP

#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralWall : public Tile {
public:
    explicit GeneralWall(const s_Tile &u_Tile);
    virtual ~GeneralWall() override = default;

    bool IsWall() override { return true; };
    bool IsDoor() override { return false; };
};
} // namespace Tiles
} // namespace Dungeon

#endif // GENERALWALL_HPP
