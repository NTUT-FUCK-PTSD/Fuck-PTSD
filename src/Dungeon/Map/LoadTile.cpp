#include "Dungeon/Map.h"

#include "Dungeon/TileFactory.h"

namespace Dungeon {
void Map::LoadTile() {
    m_MapData->ClearTiles();

    std::size_t mapIndex = 0, tmpMapIndex = 0;
    for (auto& tile : m_Level->GetTiles()) {
        mapIndex = GamePostion2MapIndex({tile.x, tile.y});
        m_MapData->AddTile(mapIndex, TileFactory::CreateTile(tile));
    }

    for (int i = 1; i < m_Size.y - 1; i++) {
        for (int j = 1; j < m_Size.x - 1; j++) {
            mapIndex = j + i * m_Size.x;
            if (m_MapData->IsTilesEmpty(mapIndex)) {
                continue;
            }
            DoorUpdate(i, j);
            // generate border
            if (!m_MapData->IsTilesEmpty(mapIndex)
                && m_MapData->GetTile(mapIndex)->GetTile().type != 102) {
                for (auto& dir : m_Direction) {
                    tmpMapIndex = j + dir.x + (i + dir.y) * m_Size.x;
                    if (i + dir.y >= 0 && i + dir.y < m_Size.y && j + dir.x >= 0
                        && j + dir.x < m_Size.x
                        && m_MapData->IsTilesEmpty(tmpMapIndex)) {
                        m_MapData->AddTile(
                            tmpMapIndex,
                            TileFactory::CreateTile(s_Tile{
                              j + dir.x + m_Level->GetLevelIndexMin().x - 1,
                              i + dir.y + m_Level->GetLevelIndexMin().y - 1,
                              102,
                              0,
                              0,
                              0
                            })
                        );
                    }
                }
            }
        }
    }

    // SetCloseDisplayB24
    for (int i = 0; i < m_Size.y; i++) {
        for (int j = 0; j < m_Size.x; j++) {
            mapIndex = j + i * m_Size.x;
            if (m_MapData->IsTilesEmpty(mapIndex)) {
                continue;
            }
            if ((1 + i >= m_Size.y)
                || (1 + i >= 0 && m_MapData->IsTilesEmpty(mapIndex + m_Size.x)
                )) {
                m_MapData->GetTile(mapIndex)->SetCloseDisplayB24(true);
            }
        }
    }

    for (auto& tile : m_MapData->GetUnsortedTiles()) {
        m_Children.push_back(tile);
    }
}

void Map::DoorUpdate(std::size_t i, std::size_t j) {
    std::size_t mapIndex = j + i * m_Size.x, tmpMapIndex = 0;
    // door direction detection
    auto tmp = m_MapData->GetTile(mapIndex);
    if (tmp->GetTile().type == 103 || tmp->GetTile().type == 106
        || tmp->GetTile().type == 111 || tmp->GetTile().type == 118) {
        std::size_t doorCount = 0;
        for (std::size_t k = 2; k < 4; k++) {
            tmpMapIndex = j + m_Direction[k].x
                          + (i + m_Direction[k].y) * m_Size.x;
            if (j + m_Direction[k].x >= 0
                && j + m_Direction[k].x < static_cast<std::size_t>(m_Size.x)
                && i + m_Direction[k].y >= 0
                && i + m_Direction[k].y < static_cast<std::size_t>(m_Size.y)
                && !m_MapData->IsTilesEmpty(tmpMapIndex)
                && (m_MapData->GetTile(tmpMapIndex)->IsWall()
                    || m_MapData->GetTile(tmpMapIndex)->IsDoor())) {
                doorCount++;
            }
        }
        if (doorCount >= 2) {
            m_MapData->RemoveTile(mapIndex);
            if (tmp->GetTile().type == 111) {
                m_MapData->AddTile(
                    mapIndex,
                    TileFactory::CreateTile(s_Tile{
                      tmp->GetTile().x,
                      tmp->GetTile().y,
                      52,
                      tmp->GetTile().zone,
                      tmp->GetTile().torch,
                      tmp->GetTile().cracked
                    })
                );
            } else {
                if (tmp->GetTile().type == 103 || tmp->GetTile().type == 118) {
                    m_MapData->AddTile(
                        mapIndex,
                        TileFactory::CreateTile(s_Tile{
                          tmp->GetTile().x,
                          tmp->GetTile().y,
                          50,
                          tmp->GetTile().zone,
                          tmp->GetTile().torch,
                          tmp->GetTile().cracked
                        })
                    );
                } else {
                    m_MapData->AddTile(
                        mapIndex,
                        TileFactory::CreateTile(s_Tile{
                          tmp->GetTile().x,
                          tmp->GetTile().y,
                          51,
                          tmp->GetTile().zone,
                          tmp->GetTile().torch,
                          tmp->GetTile().cracked
                        })
                    );
                }
            }
        }
    }
}
}  // namespace Dungeon
