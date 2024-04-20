#include "Dungeon/Tiles/WirePhaseConductor.h"

namespace Dungeon {
namespace Tiles {
WirePhaseConductor::WirePhaseConductor(const s_Tile &u_Tile)
    : GeneralFloor(u_Tile, false) {
    m_ZIndex = m_ZIndex + 1e-6;
    UpdateDrawable();
}
} // namespace Tiles
} // namespace Dungeon
