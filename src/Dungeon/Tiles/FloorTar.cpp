#include "Dungeon/Tiles/FloorTar.h"

#include "Settings/Window.hpp"

namespace Dungeon {
namespace Tiles {
FloorTar::FloorTar(const s_Tile& u_Tile)
    : GeneralFloor(u_Tile, false) {
    m_ImgSize = {m_ImgSize.x, DUNGEON_TILE_WIDTH};
    UpdateDrawable();
}
}  // namespace Tiles
}  // namespace Dungeon
