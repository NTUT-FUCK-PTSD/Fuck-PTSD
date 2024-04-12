#include "Dungeon/Tile.h"
#include "ToolBoxs.h"

namespace Dungeon {

Tile::Tile(const s_Tile &u_Tile)
    : m_Tile(u_Tile) {
    m_ZIndex = m_Tile.y;
    m_Filepath =
        (ASSETS_DIR "/level/") + DUNGEON_TILETYPES.at(m_Tile.type) + ".png";
    m_SpriteSheet = std::make_shared<Util::SpriteSheet>(m_Filepath);

    m_TileSize = DUNGEON_TILESIZES.at(m_Tile.type);
    m_ImgSize =
        ToolBoxs::CountImagePixel(m_Filepath, m_TileSize.x, m_TileSize.y);
    m_Drawable = m_SpriteSheet;
}

Tile::Tile(const s_Tile &u_Tile, const std::string &filepath)
    : m_Tile(u_Tile),
      m_Filepath(filepath) {
    m_ZIndex = m_Tile.y;
    m_SpriteSheet = std::make_shared<Util::SpriteSheet>(m_Filepath);

    m_TileSize = DUNGEON_TILESIZES.at(m_Tile.type);
    m_ImgSize =
        ToolBoxs::CountImagePixel(m_Filepath, m_TileSize.x, m_TileSize.y);
    m_Drawable = m_SpriteSheet;
}

void Tile::SetIndex(std::size_t index) {
    m_Index = index;
    UpdateDrawable();
}

void Tile::SetCloseDisplayB24(bool closeDisplayb24) {
    if (IsWall()) {
        m_CloseDisplayb24 = closeDisplayb24;
    }
    else {
        LOG_ERROR("Only wall type can be closeDisplayb24");
    }

    UpdateDrawable();
}

void Tile::SetRotation(float rotation) {
    m_Transform.rotation = rotation;
}

std::size_t Tile::GetIndex() {
    return m_Index;
}

s_Tile Tile::GetTile() {
    return m_Tile;
}

void Tile::UpdateScale() {
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
}

void Tile::UpdateTranslation() {
    m_Transform.translation = {
        (m_Tile.x * DUNGEON_TILE_WIDTH * DUNGEON_SCALE),
        -DUNGEON_TILE_WIDTH - (m_Tile.y * DUNGEON_TILE_WIDTH * DUNGEON_SCALE) +
            (m_MagicNumber / 2.0 * DUNGEON_SCALE)};
}

void Tile::UpdateDrawable() {
    UpdateScale();
    UpdateTranslation();

    if (m_ImgSize.x > DUNGEON_TILE_WIDTH) {
        m_SpriteSheet->SetDrawRect(
            {static_cast<int>(m_ImgSize.x *
                                  (m_Index % static_cast<int>(m_TileSize.x)) +
                              (m_ImgSize.x - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(m_ImgSize.y *
                                  (m_Index / static_cast<int>(m_TileSize.x)) +
                              (m_ImgSize.y - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(DUNGEON_TILE_WIDTH),
             static_cast<int>(DUNGEON_TILE_WIDTH - m_OffSetY)});
    }
    else {
        m_SpriteSheet->SetDrawRect(
            {static_cast<int>(m_ImgSize.x *
                                  (m_Index % static_cast<int>(m_TileSize.x)) +
                              (m_ImgSize.x - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(m_ImgSize.y *
                              (m_Index / static_cast<int>(m_TileSize.x))),
             static_cast<int>(DUNGEON_TILE_WIDTH),
             static_cast<int>(m_ImgSize.y - m_OffSetY)});
    }
    m_Drawable = m_SpriteSheet;
}

} // namespace Dungeon
