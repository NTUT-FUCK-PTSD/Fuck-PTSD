#include "Dungeon/Tiles/GeneralFloor.h"

#include "Settings/ToolBoxs.h"
#include "Settings/Window.hpp"

namespace Dungeon {
namespace Tiles {
GeneralFloor::GeneralFloor(const s_Tile& u_Tile, const bool generalFloor)
    : Tile(u_Tile) {
    if (generalFloor) {
        UpdateDrawable();
    }
}
}  // namespace Tiles
}  // namespace Dungeon
