#include "Dungeon/Tiles/GeneralFloor.h"

namespace Dungeon {
namespace Tiles {
GeneralFloor::GeneralFloor(const s_Tile& _Tile, const bool generalFloor)
    : Tile(_Tile) {
    if (generalFloor) { UpdateDrawable(); }
}
}  // namespace Tiles
}  // namespace Dungeon
