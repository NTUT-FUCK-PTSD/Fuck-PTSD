#include "Dungeon/Tile.h"
#include "ToolBoxs.h"

namespace Dungeon {

Tile::Tile(const s_Tile &u_Tile)
    : m_Tile(u_Tile) {
    m_ZIndex = m_Tile.y;
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

    m_TileSize = DUNGEON_TILESIZES.at(m_Tile.type);
    m_ImgSize =
        ToolBoxs::CountImagePixel(m_Filepath, m_TileSize.x, m_TileSize.y);
    if (m_Tile.type >= 100) {
        m_MagicNumber = 7;
        m_ImgSize.y -= 1;

        if (m_Tile.type >= 112 && m_Tile.type <= 117) {
            m_MagicNumber = 42;
        }
        else if (m_Tile.type == 103 || m_Tile.type == 106 ||
                 m_Tile.type == 111 || m_Tile.type == 118) {
            m_ZIndex = m_ZIndex + 0.25;
            if (m_Tile.type == 111) {
                m_MagicNumber = 26;
            }
            else {
                m_MagicNumber = 7;
            }
        }
        else if (m_Tile.type >= 120 && m_Tile.type <= 123) {
            m_MagicNumber = 38;
        }
    }
    else if (m_Tile.type == 23 || m_Tile.type == 24) {
        m_ZIndex = m_ZIndex + 0.125;
    }
    else if (m_Tile.type == 8) {
        m_ImgSize = {m_ImgSize.x, DUNGEON_TILE_WIDTH};
    }
    UpdateDrawable();
}

void Tile::SetIndex(std::size_t index) {
    m_Index = index;
    UpdateDrawable();
}

void Tile::SetCloseDisplayb24(bool closeDisplayb24) {
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

bool Tile::IsWall() {
    return m_Tile.type == 100 || m_Tile.type == 101 || m_Tile.type == 102 ||
           m_Tile.type == 104 || m_Tile.type == 105 || m_Tile.type == 107 ||
           m_Tile.type == 108 || m_Tile.type == 109 || m_Tile.type == 110 ||
           m_Tile.type == 119 || m_Tile.type == 120 || m_Tile.type == 121 ||
           m_Tile.type == 122 || m_Tile.type == 123;
}

void Tile::UpdateDrawable() {
    int offSetY = 0;
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    m_Transform.translation = {
        (m_Tile.x * DUNGEON_TILE_WIDTH * DUNGEON_SCALE),
        -DUNGEON_TILE_WIDTH - (m_Tile.y * DUNGEON_TILE_WIDTH * DUNGEON_SCALE) +
            (m_MagicNumber / 2.0 * DUNGEON_SCALE)};
    if (m_CloseDisplayb24) {
        offSetY = DUNGEON_TILE_WIDTH;
        m_Transform.translation = {m_Transform.translation.x,
                                   m_Transform.translation.y +
                                       offSetY / 2.0 * DUNGEON_SCALE};
    }

    if (m_ImgSize.x > DUNGEON_TILE_WIDTH) {
        m_SpriteSheet->SetDrawRect(
            {static_cast<int>(m_ImgSize.x *
                                  (m_Index % static_cast<int>(m_TileSize.x)) +
                              (m_ImgSize.x - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(m_ImgSize.y *
                                  (m_Index / static_cast<int>(m_TileSize.x)) +
                              (m_ImgSize.y - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(DUNGEON_TILE_WIDTH),
             static_cast<int>(DUNGEON_TILE_WIDTH - offSetY)});
    }
    else {
        m_SpriteSheet->SetDrawRect(
            {static_cast<int>(m_ImgSize.x *
                                  (m_Index % static_cast<int>(m_TileSize.x)) +
                              (m_ImgSize.x - DUNGEON_TILE_WIDTH) / 2),
             static_cast<int>(m_ImgSize.y *
                              (m_Index / static_cast<int>(m_TileSize.x))),
             static_cast<int>(DUNGEON_TILE_WIDTH),
             static_cast<int>(m_ImgSize.y - offSetY)});
    }
    m_Drawable = m_SpriteSheet;
}

} // namespace Dungeon
