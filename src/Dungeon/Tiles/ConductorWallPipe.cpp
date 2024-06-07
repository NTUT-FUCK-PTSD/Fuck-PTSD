#include "Dungeon/Tiles/ConductorWallPipe.h"

namespace Dungeon {
namespace Tiles {
ConductorWallPipe::ConductorWallPipe(const s_Tile& _Tile)
    : GeneralWall(_Tile, false) {
    m_MagicNumber = 38;
    UpdateDrawable();
}
}  // namespace Tiles
}  // namespace Dungeon
