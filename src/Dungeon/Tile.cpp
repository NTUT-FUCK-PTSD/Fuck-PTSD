#include "Dungeon/Tile.h"
#include "ToolBoxs.h"

namespace Dungeon {

Tile::Tile(const tile &u_Tile)
    : m_Tile(u_Tile) {
    m_filepath =
        (ASSETS_DIR "/level/") + DUNGEON_TILETYPES.at(m_Tile.type) + ".png";
    if (m_Tile.type >= 100) {
        SetZIndex(1);
    }
    if (m_Tile.type >= 112 && m_Tile.type <= 117) {
        m_filepath = (ASSETS_DIR "necrodancer_stage.png");
    }
    else if (m_Tile.type == 118) {
        m_filepath = (ASSETS_DIR "door_front.png");
    }
    m_SpriteSheet = std::make_shared<Util::SpriteSheet>(m_filepath);
    Update();
}

void Tile::SetIndex(std::size_t index) {
    m_Index = index;
    Update();
}

std::size_t Tile::GetIndex() {
    return m_Index;
}

void Tile::Update() {
    m_TileSize = DUNGEON_TILESIZES.at(m_Tile.type);
    auto ImgSize =
        ToolBoxs::CountImagePixel(m_filepath, m_TileSize.x, m_TileSize.y);
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    m_Transform.translation = {
        (m_Tile.x * DUNGEON_TILE_WIDTH * DUNGEON_SCALE),
        -(m_Tile.y * DUNGEON_TILE_WIDTH * DUNGEON_SCALE)};

    m_SpriteSheet->SetDrawRect(
        {static_cast<int>(ImgSize.x * m_Index), static_cast<int>(ImgSize.y * 0),
         static_cast<int>(DUNGEON_TILE_WIDTH), static_cast<int>(ImgSize.y)});
    m_Drawable = m_SpriteSheet;
}

} // namespace Dungeon
