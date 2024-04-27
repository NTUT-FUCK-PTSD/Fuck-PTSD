#include "Dungeon/Tiles/WireDoor.h"

namespace Dungeon {
namespace Tiles {
WireDoor::WireDoor(const s_Tile& u_Tile)
    : GeneralDoor(u_Tile, (ASSETS_DIR "/level/door_front.png"), false) {
    UpdateDrawable();
}
}  // namespace Tiles
}  // namespace Dungeon
