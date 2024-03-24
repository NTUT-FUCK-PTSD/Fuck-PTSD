#include "Dungeon/Enemies/BlueSlime.h"
#include "Dungeon/Map.h"

namespace Dungeon {

Map::Map(const std::shared_ptr<Camera> &camera, const std::string &path,
         const int &levelNum)
    : m_Camera(camera) {
    m_Level = std::make_unique<Level>(path, levelNum);

    m_Size = m_Level->GetLevelIndexMax() - m_Level->GetLevelIndexMin() +
             3; // add 3 for the border
    m_MapData.resize(m_Size.x * m_Size.y);
    size_t mapIndex = 0, tmpMapIndex = 0;

    for (auto &tile : m_Level->GetTiles()) {
        mapIndex = (tile.x - m_Level->GetLevelIndexMin().x + 1) +
                   (tile.y - m_Level->GetLevelIndexMin().y + 1) * m_Size.x;
        if (tile.type == 23 || tile.type == 24 || tile.type == 103 ||
            tile.type == 106 || tile.type == 111 || tile.type == 118) {
            m_MapData[mapIndex].tiles.push_back(std::make_shared<Tile>(s_Tile{
                tile.x, tile.y, 0, tile.zone, tile.torch, tile.cracked}));
            m_Tiles.push_back(m_MapData[mapIndex].tiles.back());
        }
        m_MapData[mapIndex].tiles.push_back(std::make_shared<Tile>(tile));
        m_Tiles.push_back(m_MapData[mapIndex].tiles.back());
    }

    std::vector<glm::ivec2> direction = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
                                         {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 1; i < m_Size.y - 1; i++) {
        for (int j = 1; j < m_Size.x - 1; j++) {
            mapIndex = j + i * m_Size.x;
            if (m_MapData[mapIndex].tiles.empty()) {
                continue;
            }
            // door direction detection
            auto tmp = m_MapData[mapIndex].tiles.back();
            size_t doorCount = 0;
            if (tmp->GetTile().type == 103 || tmp->GetTile().type == 106 ||
                tmp->GetTile().type == 111 || tmp->GetTile().type == 118) {
                for (size_t k = 2; k < 4; k++) {
                    tmpMapIndex =
                        j + direction[k].x + (i + direction[k].y) * m_Size.x;
                    if (j + direction[k].x >= 0 &&
                        j + direction[k].x < m_Size.x &&
                        i + direction[k].y >= 0 &&
                        i + direction[k].y < m_Size.y &&
                        !m_MapData[tmpMapIndex].tiles.empty() &&
                        (m_MapData[tmpMapIndex].tiles.back()->IsWall())) {
                        doorCount++;
                    }
                }
                if (doorCount >= 2) {
                    m_MapData[mapIndex].tiles.pop_back();
                    m_Tiles.erase(
                        std::remove(m_Tiles.begin(), m_Tiles.end(), tmp),
                        m_Tiles.end()); // Remove Child
                    if (tmp->GetTile().type == 111) {
                        m_MapData[mapIndex].tiles.push_back(
                            std::make_shared<Tile>(s_Tile{
                                tmp->GetTile().x, tmp->GetTile().y, 52,
                                tmp->GetTile().zone, tmp->GetTile().torch,
                                tmp->GetTile().cracked}));
                    }
                    else {
                        if (tmp->GetTile().type == 103 ||
                            tmp->GetTile().type == 118) {
                            m_MapData[mapIndex].tiles.push_back(
                                std::make_shared<Tile>(s_Tile{
                                    tmp->GetTile().x, tmp->GetTile().y, 50,
                                    tmp->GetTile().zone, tmp->GetTile().torch,
                                    tmp->GetTile().cracked}));
                        }
                        else {
                            m_MapData[mapIndex].tiles.push_back(
                                std::make_shared<Tile>(s_Tile{
                                    tmp->GetTile().x, tmp->GetTile().y, 51,
                                    tmp->GetTile().zone, tmp->GetTile().torch,
                                    tmp->GetTile().cracked}));
                        }
                    }
                    m_Tiles.push_back(m_MapData[mapIndex].tiles.back());
                }
            }
            // generate border
            if (m_MapData[mapIndex].tiles.back()->GetTile().type != 102) {
                for (auto &dir : direction) {
                    tmpMapIndex = j + dir.x + (i + dir.y) * m_Size.x;
                    if (i + dir.y >= 0 && i + dir.y < m_Size.y &&
                        j + dir.x >= 0 && j + dir.x < m_Size.x &&
                        m_MapData[tmpMapIndex].tiles.empty()) {
                        m_MapData[tmpMapIndex].tiles.push_back(
                            std::make_shared<Tile>(s_Tile{
                                j + dir.x + m_Level->GetLevelIndexMin().x - 1,
                                i + dir.y + m_Level->GetLevelIndexMin().y - 1,
                                102, 0, 0, 0}));
                        m_Tiles.push_back(m_MapData[tmpMapIndex].tiles.back());
                    }
                }
            }
        }
    }

    // SetCloseDisplayb24
    for (int i = 0; i < m_Size.y; i++) {
        for (int j = 0; j < m_Size.x; j++) {
            mapIndex = j + i * m_Size.x;
            if (m_MapData[mapIndex].tiles.empty()) {
                continue;
            }
            if ((1 + i >= m_Size.y) ||
                (1 + i >= 0 && m_MapData[mapIndex + m_Size.x].tiles.empty())) {
                m_MapData[mapIndex].tiles.back()->SetCloseDisplayb24(true);
            }
        }
    }

    // Add a BlueSlime for testing
    m_MapData[1 + 1 * m_Size.x].enemies.push_back(
        std::make_shared<Enemies::BlueSlime>(s_Enemy{1, 1, 0, 0, 0}));
    m_Enemies.push_back(m_MapData[1 + 1 * m_Size.x].enemies.back());

    m_Visible = false;
    for (auto &tile : m_Tiles) {
        m_Camera->AddChild(tile);
    }
    for (auto &enemy : m_Enemies) {
        m_Camera->AddChild(enemy);
    }
    Update();
}

void Map::SetVisible(const bool &visible) {
    m_Visible = visible;
    Update();
}

void Map::Update() {
    // size_t mapIndex = 0;
    // for (int i = 0; i < m_Size.y; i++) {
    //     for (int j = 0; j < m_Size.x; j++) {
    //         mapIndex = j + i * m_Size.x;
    //         for (auto &tile : m_MapData[mapIndex].tiles) {
    //             tile->SetVisible(m_Visible);
    //         }
    //         for (auto &enemy : m_MapData[mapIndex].enemies) {
    //             enemy->SetVisible(m_Visible);
    //         }
    //     }
    // }
    for (auto &tile : m_Tiles) {
        tile->SetVisible(m_Visible);
    }
    for (auto &enemy : m_Enemies) {
        enemy->SetVisible(m_Visible);
    }
}

void Map::TempoUpdate() {
    // size_t mapIndex = 0;
    // for (int i = 0; i < m_Size.y; i++) {
    //     for (int j = 0; j < m_Size.x; j++) {
    //         mapIndex = j + i * m_Size.x;
    //         for (auto &enemy : m_MapData[mapIndex].enemies) {
    //             enemy->TempoMove();
    //         }
    //     }
    // }
    for (auto &enemy : m_Enemies) {
        enemy->TempoMove();
    }
}

} // namespace Dungeon
