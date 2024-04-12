#include "Dungeon/Tiles/GeneralDoor.h"

namespace Dungeon {
namespace Tiles {
GeneralDoor::GeneralDoor(const s_Tile &u_Tile)
    : Tile(u_Tile) {
    m_ZIndex = m_ZIndex + 0.125;
}
} // namespace Tiles
} // namespace Dungeon
