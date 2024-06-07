#include "Dungeon/Tiles/WirePhaseConductor.h"

namespace Dungeon {
namespace Tiles {
WirePhaseConductor::WirePhaseConductor(const s_Tile& _Tile)
    : GeneralFloor(_Tile, false) {
    m_ZIndex = m_ZIndex + 0.125f;
    UpdateDrawable();
}
}  // namespace Tiles
}  // namespace Dungeon
