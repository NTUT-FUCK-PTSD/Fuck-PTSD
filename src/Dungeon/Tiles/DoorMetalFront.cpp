#include "Dungeon/Tiles/DoorMetalFront.h"

namespace Dungeon {
namespace Tiles {
DoorMetalFront::DoorMetalFront(const s_Tile& _Tile)
    : GeneralDoor(_Tile, false) {
    m_MagicNumber = 26;
    UpdateDrawable();
}
}  // namespace Tiles
}  // namespace Dungeon
