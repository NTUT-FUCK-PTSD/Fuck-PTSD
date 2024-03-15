#include "Dungeon/Tile.h"
#include "ToolBoxs.h"

namespace Dungeon {

Tile::Tile(const s_Tile &u_Tile)
    : m_Tile(u_Tile) {
    SetZIndex(m_Tile.y);
    m_Filepath =
        (ASSETS_DIR "/level/") + DUNGEON_TILETYPES.at(m_Tile.type) + ".png";
    if (m_Tile.type >= 112 && m_Tile.type <= 117) {
        m_Filepath = (ASSETS_DIR "/level/necrodancer_stage.png");
        m_Index = m_Tile.type - 112;
    }
    else if (m_Tile.type == 118) {
        m_Filepath = (ASSETS_DIR "/level/door_front.png");
    }
    m_SpriteSheet = std::make_shared<Util::SpriteSheet>(m_Filepath);
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
        ToolBoxs::CountImagePixel(m_Filepath, m_TileSize.x, m_TileSize.y);

    int8_t magicNumber = 0;
    if (m_Tile.type >= 100) {
        magicNumber = 7;
        ImgSize.y -= 1;

        if (m_Tile.type >= 112 && m_Tile.type <= 117) {
            magicNumber = 42;
        }
        else if (m_Tile.type == 103 || m_Tile.type == 106 ||
                 m_Tile.type == 111 || m_Tile.type == 118) {
            SetZIndex(m_Tile.y + 1);
            if (m_Tile.type == 111) {
                magicNumber = 26;
            }
            else {
                magicNumber = 7;
            }
        }
    }
    else if (m_Tile.type == 8) {
        ImgSize = {ImgSize.x, DUNGEON_TILE_WIDTH};
    }
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    m_Transform.translation = {
        (m_Tile.x * DUNGEON_TILE_WIDTH * DUNGEON_SCALE),
        -DUNGEON_TILE_WIDTH - (m_Tile.y * DUNGEON_TILE_WIDTH * DUNGEON_SCALE) +
            (magicNumber / 2.0 * DUNGEON_SCALE)};
    if (ImgSize.x > DUNGEON_TILE_WIDTH) {
        m_SpriteSheet->SetDrawRect(
            {static_cast<int>(ImgSize.x *
                                  (m_Index % static_cast<int>(m_TileSize.x)) +
                              (ImgSize.x - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(ImgSize.y *
                                  (m_Index / static_cast<int>(m_TileSize.x)) +
                              (ImgSize.y - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(DUNGEON_TILE_WIDTH),
             static_cast<int>(DUNGEON_TILE_WIDTH)});
    }
    else {
        m_SpriteSheet->SetDrawRect(
            {static_cast<int>(ImgSize.x *
                                  (m_Index % static_cast<int>(m_TileSize.x)) +
                              (ImgSize.x - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(ImgSize.y *
                              (m_Index / static_cast<int>(m_TileSize.x))),
             static_cast<int>(DUNGEON_TILE_WIDTH),
             static_cast<int>(ImgSize.y)});
    }
    m_Drawable = m_SpriteSheet;
}

} // namespace Dungeon
