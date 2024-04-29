#include "Dungeon/Tiles/DoorMetalFront.h"

namespace Dungeon {
namespace Tiles {
DoorMetalFront::DoorMetalFront(const s_Tile& u_Tile)
    : GeneralDoor(u_Tile, false) {
    m_MagicNumber = 26;
    UpdateDrawable();
}
}  // namespace Tiles
}  // namespace Dungeon
