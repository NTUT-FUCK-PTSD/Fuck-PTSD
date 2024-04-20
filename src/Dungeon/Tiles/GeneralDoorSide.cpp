#include "Dungeon/Tiles/GeneralDoorSide.h"

namespace Dungeon {
namespace Tiles {
GeneralDoorSide::GeneralDoorSide(const s_Tile &u_Tile,
                                 const bool generalDoorSide)
    : Tile(u_Tile) {
    m_ZIndex = m_ZIndex + 1e-4;
    m_MagicNumber = 7;
    if (generalDoorSide) {
        UpdateDrawable();
    }
}
} // namespace Tiles
} // namespace Dungeon
