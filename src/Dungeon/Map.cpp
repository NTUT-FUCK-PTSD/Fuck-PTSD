#include "Dungeon/Map.h"

#include "Dungeon/EnemyFactory.h"
#include "Dungeon/TileFactory.h"
#include "MapEvent.h"
namespace Dungeon {

Map::Map(
    const std::shared_ptr<Camera> camera,
    const std::string&            path,
    const std::size_t             levelNum
)
    : m_Camera(camera) {
    // ZIndex 98~100 is for UI
    m_ZIndex = 98;
    m_Transform.scale = {DUNGEON_SCALE + 1, DUNGEON_SCALE + 1};
    m_Transform.translation = {0, 0};
    m_Level = std::make_unique<Level>(path);
    m_Available = LoadLevel(levelNum);

    // Add enemy testing
    // auto mapIndex = GamePostion2MapIndex({1, 1});
    // auto enemy = EnemyFactory::CreateEnemy(s_Enemy{1, 1, 11, 0, 0},
    // m_MapData); m_MapData->AddEnemy(mapIndex, enemy);
    // m_Children.push_back(enemy);

    InitEvent();
}

void Map::InitEvent() {
    MapEvent::AttackPlayer.append([this](const std::size_t damage) {
        (void)damage;
        m_Camera->Shake(100, 10);
        m_OverlayRed = true;
        m_OverlayRedTime = Util::Time::GetElapsedTimeMs();
    });

    MapEvent::EnemyMove.append(
        [this](const std::size_t srcMapIndex, const std::size_t destMapIndex) {
            auto enemy = m_MapData->GetEnemy(srcMapIndex);
            if (enemy) {
                auto gamePosition = MapIndex2GamePosition(destMapIndex);
                enemy->SetGamePosition(gamePosition);
                m_MapData->MoveEnemy(srcMapIndex, destMapIndex);
                if (CheckShowPosition(
                        gamePosition,
                        m_MapData->GetPlayerPosition()
                    )) {
                    enemy->SetCameraUpdate(true);
                    if (CanPlayerSeePosition(gamePosition)) {
                        enemy->SetShadow(false);
                    } else {
                        enemy->SetShadow(true);
                    }
                }
                m_MiniMap->UpdateCubeColor(srcMapIndex);
                m_MiniMap->UpdateCubeColor(destMapIndex);
            }
        }
    );

    MapEvent::PlayerMove.append([this](const glm::vec2& gamePosition) {
        m_MapData->SetPlayerPosition(gamePosition);
        CameraUpdate();
    });

    MapEvent::ResetMap.append([this]() {
        m_Children.clear();
        if (m_MapData) {
            m_MapData->ClearTiles();
            m_MapData->ClearEnemies();
        }
        if (m_MiniMap) {
            m_Camera->RemoveUIChild(m_MiniMap);
        }

        m_Camera->SetPosition({0, 0});
    });
}

Map::~Map() {
    MapEvent::ResetMap();
}

bool Map::LoadLevel(const std::size_t levelNum) {
    MapEvent::ResetMap();

    if (!m_Level->LoadLevel(levelNum)) {
        m_Available = false;
        return false;
    }
    m_LevelNum = levelNum;

    m_Size = m_Level->GetLevelIndexMax() - m_Level->GetLevelIndexMin()
             + 3;  // add 3 for the border
    m_MapData = std::make_shared<MapData>(
        m_Level->GetLevelIndexMin(),
        m_Level->GetLevelIndexMax(),
        m_Size
    );

    LoadTile();
    LoadEnemy();
    if (m_MiniMap) {
        m_Camera->RemoveUIChild(m_MiniMap);
    }
    m_MiniMap = std::make_shared<MiniMap>(m_MapData);
    m_Camera->AddUIChild(m_MiniMap);

    m_ShadowRenderDP.clear();
    m_ShadowRenderDP.resize(m_Size.x * m_Size.y, false);
    CameraUpdate();
    m_MiniMap->Update();
    return true;
}

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

    for (auto& tile : m_MapData->GetTilesQueue()) {
        m_Children.push_back(tile);
    }
}  // namespace Dungeon

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

void Map::LoadEnemy() {
    m_MapData->ClearEnemies();

    std::size_t mapIndex = 0;
    for (auto& enemy : m_Level->GetEnemies()) {
        mapIndex = GamePostion2MapIndex({enemy.x, enemy.y});
        m_MapData->AddEnemy(
            mapIndex,
            EnemyFactory::CreateEnemy(enemy, m_MapData)
        );
    }

    for (auto& enemy : m_MapData->GetEnemyQueue()) {
        m_Children.push_back(enemy);
    }
}

std::size_t Map::GetLevelNum() const {
    return m_LevelNum;
}

bool Map::CheckShowPosition(
    const glm::vec2& position1,
    const glm::vec2& position2
) {
    return (
        position1.x >= position2.x - (ALLOW_EXTRA_DRAW + HalfColNumber)
        && position1.x <= position2.x + (ALLOW_EXTRA_DRAW + HalfColNumber)
        && position1.y >= position2.y - (ALLOW_EXTRA_DRAW + HalfRowNumber)
        && position1.y <= position2.y + (ALLOW_EXTRA_DRAW + HalfRowNumber)
    );
}

void Map::CameraUpdate() {
    glm::vec2 cameraPos = m_MapData->GetPlayerPosition();

    for (auto& tile : m_MapData->GetTilesQueue()) {
        if (CheckShowPosition(
                {tile->GetTile().x, tile->GetTile().y},
                cameraPos
            )) {
            tile->SetCameraUpdate(true);
            if (CanPlayerSeePosition({tile->GetTile().x, tile->GetTile().y})) {
                tile->SetOverlay(false);
            } else {
                tile->SetOverlay(true);
            }
            m_MiniMap->UpdateCubeColor(
                GamePostion2MapIndex({tile->GetTile().x, tile->GetTile().y})
            );
        } else {
            tile->SetCameraUpdate(false);
        }
    }
    for (auto& enemy : m_MapData->GetEnemyQueue()) {
        if (CheckShowPosition(enemy->GetGamePosition(), cameraPos)) {
            enemy->SetCameraUpdate(true);
            if (CanPlayerSeePosition(enemy->GetGamePosition())) {
                enemy->SetShadow(false);
            } else {
                enemy->SetShadow(true);
            }
            m_MiniMap->UpdateCubeColor(
                GamePostion2MapIndex(enemy->GetGamePosition())
            );
        } else {
            enemy->SetCameraUpdate(false);
        }
    }
}

void Map::TempoUpdate(bool isPlayer) {
    m_TempoAttack = false;
    if (!isPlayer) {
        for (auto& enemy : m_MapData->GetEnemyQueue()) {
            enemy->TempoMove();
        }
    } else {
        m_ShadowRenderDP.clear();
        m_ShadowRenderDP.resize(m_Size.x * m_Size.y, false);
    }
    Update();
}

void Map::PlayerTrigger() {
    TempoUpdate(true);
}

void Map::TempoTrigger(const std::size_t index) {
    if (m_TempoIndex == index) {
        return;
    }
    m_TempoIndex = index;
    TempoUpdate(false);
}

void Map::Update() {
    m_Transform.translation = {0, 0};

    if (m_OverlayRedTime + 200 < Util::Time::GetElapsedTimeMs()) {
        m_OverlayRed = false;
    }

    MapEvent::DrawableUpdate();
}

std::size_t Map::GamePostion2MapIndex(const glm::ivec2& position) const {
    return (position.x - m_Level->GetLevelIndexMin().x + 1)
           + (position.y - m_Level->GetLevelIndexMin().y + 1) * m_Size.x;
}

glm::ivec2 Map::MapIndex2GamePosition(const std::size_t index) const {
    return {
      static_cast<int>(index % m_Size.x) + m_Level->GetLevelIndexMin().x - 1,
      static_cast<int>(index / m_Size.x) + m_Level->GetLevelIndexMin().y - 1
    };
}

std::shared_ptr<MapData> Map::GetMapData() const {
    return m_MapData;
}

bool Map::isVaildPosition(const glm::ivec2& position) {
    if (position.x < m_Level->GetLevelIndexMin().x
        || position.x > m_Level->GetLevelIndexMax().x
        || position.y < m_Level->GetLevelIndexMin().y
        || position.y > m_Level->GetLevelIndexMax().y) {
        return false;
    }
    return true;
}

bool Map::isVaildMove(const glm::ivec2& position) {
    std::size_t mapIndex = GamePostion2MapIndex(position);
    if (m_MapData->IsTilesEmpty(mapIndex)) {
        return false;
    }
    if (m_MapData->GetTile(mapIndex)->IsWall()) {
        return false;
    }
    return true;
}

void Map::RemoveEnemy(const std::size_t position) {
    m_Children.erase(
        std::remove(
            m_Children.begin(),
            m_Children.end(),
            m_MapData->GetEnemy(position)
        ),
        m_Children.end()
    );
    m_MapData->RemoveEnemy(position);
}

void Map::RemoveWall(const std::size_t position) {
    auto tile = m_MapData->GetTile(position)->GetTile();

    if (tile.type == 102) {
        return;
    }
    m_Children.erase(
        std::remove(
            m_Children.begin(),
            m_Children.end(),
            m_MapData->GetTile(position)
        ),
        m_Children.end()
    );
    m_MapData->RemoveTile(position);
    m_MapData->AddTile(
        position,
        TileFactory::CreateTile(
            s_Tile{tile.x, tile.y, 0, tile.zone, 0, tile.cracked}
        )
    );
    m_Children.push_back(m_MapData->GetTile(position));
}

void Map::OpenDoor(const std::size_t position) {
    auto tile = m_MapData->GetTile(position)->GetTile();
    auto doorType = tile.type;
    auto gamePosition = glm::vec2(tile.x, tile.y);

    if (doorType == 50 || doorType == 103 || doorType == 118) {
        for (size_t i = 0; i < 4; i++) {
            auto tmpPosition = gamePosition + m_EnemyMove[i];
            auto tmpMapIndex = GamePostion2MapIndex(tmpPosition);
            if (m_MapData->IsPositionDoor(tmpPosition)
                && doorType
                       == m_MapData->GetTile(tmpMapIndex)->GetTile().type) {
                m_Children.erase(
                    std::remove(
                        m_Children.begin(),
                        m_Children.end(),
                        m_MapData->GetTile(tmpMapIndex)
                    ),
                    m_Children.end()
                );
                m_MapData->RemoveTile(tmpMapIndex);
                m_MapData->AddTile(
                    position,
                    TileFactory::CreateTile(
                        s_Tile{tile.x, tile.y, 0, tile.zone, 0, tile.cracked}
                    )
                );
                m_Children.push_back(m_MapData->GetTile(position));
            }
        }
        m_Children.erase(
            std::remove(
                m_Children.begin(),
                m_Children.end(),
                m_MapData->GetTile(position)
            ),
            m_Children.end()
        );
        m_MapData->RemoveTile(position);
        m_MapData->AddTile(
            position,
            TileFactory::CreateTile(
                s_Tile{tile.x, tile.y, 0, tile.zone, 0, tile.cracked}
            )
        );
        m_Children.push_back(m_MapData->GetTile(position));
    }
}

bool Map::CanPlayerSeePosition(const glm::vec2& position) {
    // BresenhamLine Algorithm
    // glm::vec2 targetPosition = position;
    // glm::vec2 sourcePosition = m_MapData->GetPlayerPosition();

    // I don't know why but the target and source position are reversed
    // so I have to reverse them
    glm::vec2 targetPosition = m_MapData->GetPlayerPosition();
    glm::vec2 sourcePosition = position;

    std::vector<glm::vec2> integerCoordinates;

    glm::vec2 delta = targetPosition - sourcePosition;
    glm::vec2 sign = glm::sign(delta);
    delta = glm::abs(delta);
    int       error = 0;
    glm::vec2 current = sourcePosition;

    if (delta.x > delta.y) {
        for (int i = 0; i <= delta.x; ++i) {
            integerCoordinates.push_back(current);
            error -= delta.y;
            if (error < 0) {
                current.y += sign.y;
                error += delta.x;
            }
            current.x += sign.x;
        }
    } else {
        for (int i = 0; i <= delta.y; ++i) {
            integerCoordinates.push_back(current);
            error -= delta.x;
            if (error < 0) {
                current.x += sign.x;
                error += delta.y;
            }
            current.y += sign.y;
        }
    }

    std::size_t mapIndex;
    // because the integerCoordinates is from target to source
    // so we have to reverse it
    for (int i = integerCoordinates.size() - 1; i >= 0; --i) {
        mapIndex = m_MapData->GamePosition2MapIndex(integerCoordinates[i]);
        if (position == integerCoordinates[i]) {
            m_ShadowRenderDP[mapIndex] = true;
            return true;
        }
        if (m_MapData->IsPositionWall(integerCoordinates[i])
            || m_MapData->IsPositionDoor(integerCoordinates[i])) {
            m_ShadowRenderDP[mapIndex] = false;
            return false;
        }
    }
    m_ShadowRenderDP[m_MapData->GamePosition2MapIndex(position)] = true;
    return true;
}

}  // namespace Dungeon

glm::ivec2                      Dungeon::Map::m_Size = {0, 0};
std::unique_ptr<Dungeon::Level> Dungeon::Map::m_Level = nullptr;
