#include "Dungeon/Tiles/DoorMetalSide.h"

#include "Settings/Window.hpp"

namespace Dungeon {
namespace Tiles {
DoorMetalSide::DoorMetalSide(const s_Tile& u_Tile)
    : GeneralDoorSide(u_Tile, false) {
    m_ZIndex = m_ZIndex + 1e-4;
    m_MagicNumber = 15;
    UpdateDoorMetalSideDrawable();
}

void DoorMetalSide::UpdateDoorMetalSideDrawable() {
    UpdateScale();
    UpdateTranslation();
    m_Transform.translation = {
      m_Transform.translation.x - DUNGEON_TILE_WIDTH,
      m_Transform.translation.y
    };
    m_SpriteSheet->SetDrawRect(
        {static_cast<int>(
             m_ImgSize.x * (m_Index % static_cast<int>(m_TileSize.x))
         ),
         static_cast<int>(
             m_ImgSize.y * (m_Index / static_cast<int>(m_TileSize.x))
         ),
         static_cast<int>(m_ImgSize.x),
         static_cast<int>(m_ImgSize.y - m_OffSetY)}
    );
    m_Drawable = m_SpriteSheet;
}

void DoorMetalSide::UpdateDrawable() {
    UpdateDoorMetalSideDrawable();
}

}  // namespace Tiles
}  // namespace Dungeon
