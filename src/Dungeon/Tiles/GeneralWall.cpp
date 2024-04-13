#include "Dungeon/Tiles/GeneralWall.h"

#include "Settings/Window.hpp"

namespace Dungeon {
namespace Tiles {
GeneralWall::GeneralWall(const s_Tile &u_Tile, const bool generalWall)
    : Tile(u_Tile) {
    m_MagicNumber = 7;
    m_ImgSize.y -= 1;
    if (generalWall) {
        UpdateDrawable();
    }
}

GeneralWall::GeneralWall(const s_Tile &u_Tile, const std::string &filePath,
                         const bool generalWall)
    : Tile(u_Tile, filePath) {
    m_MagicNumber = 7;
    m_ImgSize.y -= 1;
    if (generalWall) {
        UpdateDrawable();
    }
}

void GeneralWall::UpdateTranslation() {
    Tile::UpdateTranslation();
    if (m_CloseDisplayb24) {
        m_OffSetY = DUNGEON_TILE_WIDTH;
        m_Transform.translation = {m_Transform.translation.x,
                                   m_Transform.translation.y +
                                       m_OffSetY / 2.0 * DUNGEON_SCALE};
    }
}
} // namespace Tiles
} // namespace Dungeon
