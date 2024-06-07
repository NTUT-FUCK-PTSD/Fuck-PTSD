#include "Dungeon/Tiles/GeneralWall.h"

#include "Settings/Window.hpp"

namespace Dungeon {
namespace Tiles {
GeneralWall::GeneralWall(const s_Tile& _Tile, const bool generalWall)
    : Tile(_Tile) {
    m_MagicNumber = 6;
    if (generalWall) { UpdateDrawable(); }
}

GeneralWall::GeneralWall(
    const s_Tile&      _Tile,
    const std::string& filePath,
    const bool         generalWall
)
    : Tile(_Tile, filePath) {
    m_MagicNumber = 6;
    if (generalWall) { UpdateDrawable(); }
}

void GeneralWall::UpdateTranslation() {
    Tile::UpdateTranslation();
    if (m_CloseDisplayb24) {
        m_OffSetY = Window::TileWidth;
        m_Transform.translation = {
          m_Transform.translation.x,
          m_Transform.translation.y + m_OffSetY / 2.0 * Window::Scale
        };
    }
}
}  // namespace Tiles
}  // namespace Dungeon
