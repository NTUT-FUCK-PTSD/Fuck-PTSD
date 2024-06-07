#include "Dungeon/Tiles/FloorTar.h"

#include "Settings/Window.hpp"

namespace Dungeon {
namespace Tiles {
FloorTar::FloorTar(const s_Tile& _Tile)
    : GeneralFloor(_Tile, false) {
    m_ImgSize = {m_ImgSize.x, Window::TileWidth};
    UpdateDrawable();
}
}  // namespace Tiles
}  // namespace Dungeon
