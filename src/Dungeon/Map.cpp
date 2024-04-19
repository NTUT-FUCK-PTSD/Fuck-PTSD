#include "Dungeon/Map.h"

#include "Dungeon/EnemyFactory.h"
#include "Dungeon/TileFactory.h"

namespace Dungeon {

Map::Map(const std::shared_ptr<Camera> camera,
         const std::shared_ptr<Camera> UIcamera,
         const std::shared_ptr<Player> mainCharacter, const std::string &path,
         const std::size_t levelNum)
    : m_Camera(camera),
      m_UIcamera(UIcamera),
      m_MainCharacter(mainCharacter) {
    // ZIndex 100 is top
    m_ZIndex = 100;
    m_Transform.scale = {DUNGEON_SCALE + 1, DUNGEON_SCALE + 1};
    m_Transform.translation = {0, 0};
    m_Level = std::make_unique<Level>(path);
    m_Available = LoadLevel(levelNum);

    // Add testing
    auto mapIndex = GamePostion2MapIndex({1, 1});
    auto enemy = EnemyFactory::CreateEnemy(s_Enemy{1, 1, 11, 0, 0}, m_MapData);
    m_MapData->AddEnemy(mapIndex, enemy);
    m_Children.push_back(enemy);
}

Map::~Map() {
    m_Children.clear();
    m_MapData->ClearTiles();
    m_MapData->ClearEnemies();
    m_UIcamera->RemoveChild(m_MiniMap);
}

bool Map::LoadLevel(const std::size_t levelNum) {
    m_Children.clear();
    if (m_MapData) {
        m_MapData->ClearTiles();
        m_MapData->ClearEnemies();
    }
    if (m_MiniMap) {
        m_UIcamera->RemoveChild(m_MiniMap);
    }

    if (!m_Level->LoadLevel(levelNum)) {
        m_Available = false;
        return false;
    }
    m_LevelNum = levelNum;
    m_Camera->SetPosition({0, 0});
    m_MainCharacter->SetGamePosition({0, 0});

    m_Size = m_Level->GetLevelIndexMax() - m_Level->GetLevelIndexMin() +
             3; // add 3 for the border
    m_MapData = std::make_shared<MapData>(m_Level->GetLevelIndexMin(),
                                          m_Level->GetLevelIndexMax(), m_Size);
    m_MapData->SetPlayerPosition(m_MainCharacter->GetGamePosition());

    LoadTile();
    LoadEnemy();
    if (m_MiniMap) {
        m_UIcamera->RemoveChild(m_MiniMap);
    }
    m_MiniMap = std::make_shared<MiniMap>(m_MapData);
    m_UIcamera->AddChild(m_MiniMap);

    m_ShadowRenderDP.clear();
    m_ShadowRenderDP.resize(m_Size.x * m_Size.y, false);
    CameraUpdate();
    return true;
}

void Map::LoadTile() {
    m_MapData->ClearTiles();

    std::size_t mapIndex = 0, tmpMapIndex = 0;
    for (auto &tile : m_Level->GetTiles()) {
        mapIndex = GamePostion2MapIndex({tile.x, tile.y});
        if (tile.type == 23 || tile.type == 24 || tile.type == 103 ||
            tile.type == 106 || tile.type == 111 || tile.type == 118) {
            m_MapData->AddTile(mapIndex, TileFactory::CreateTile(s_Tile{
                                             tile.x, tile.y, 0, tile.zone,
                                             tile.torch, tile.cracked}));
        }
        m_MapData->AddTile(mapIndex, TileFactory::CreateTile(tile));
    }

    std::vector<glm::ivec2> direction = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
                                         {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 1; i < m_Size.y - 1; i++) {
        for (int j = 1; j < m_Size.x - 1; j++) {
            mapIndex = j + i * m_Size.x;
            if (m_MapData->IsTilesEmpty(mapIndex)) {
                continue;
            }
            // door direction detection
            auto tmp = m_MapData->GetTileBack(mapIndex);
            std::size_t doorCount = 0;
            if (tmp->GetTile().type == 103 || tmp->GetTile().type == 106 ||
                tmp->GetTile().type == 111 || tmp->GetTile().type == 118) {
                for (std::size_t k = 2; k < 4; k++) {
                    tmpMapIndex =
                        j + direction[k].x + (i + direction[k].y) * m_Size.x;
                    if (j + direction[k].x >= 0 &&
                        j + direction[k].x < m_Size.x &&
                        i + direction[k].y >= 0 &&
                        i + direction[k].y < m_Size.y &&
                        !m_MapData->IsTilesEmpty(tmpMapIndex) &&
                        (m_MapData->GetTileBack(tmpMapIndex)->IsWall() ||
                         m_MapData->GetTileBack(tmpMapIndex)->IsDoor())) {
                        doorCount++;
                    }
                }
                if (doorCount >= 2) {
                    m_MapData->PopBackTile(mapIndex);
                    if (tmp->GetTile().type == 111) {
                        m_MapData->AddTile(
                            mapIndex,
                            TileFactory::CreateTile(s_Tile{
                                tmp->GetTile().x, tmp->GetTile().y, 52,
                                tmp->GetTile().zone, tmp->GetTile().torch,
                                tmp->GetTile().cracked}));
                    }
                    else {
                        if (tmp->GetTile().type == 103 ||
                            tmp->GetTile().type == 118) {
                            m_MapData->AddTile(
                                mapIndex,
                                TileFactory::CreateTile(s_Tile{
                                    tmp->GetTile().x, tmp->GetTile().y, 50,
                                    tmp->GetTile().zone, tmp->GetTile().torch,
                                    tmp->GetTile().cracked}));
                        }
                        else {
                            m_MapData->AddTile(
                                mapIndex,
                                TileFactory::CreateTile(s_Tile{
                                    tmp->GetTile().x, tmp->GetTile().y, 51,
                                    tmp->GetTile().zone, tmp->GetTile().torch,
                                    tmp->GetTile().cracked}));
                        }
                    }
                }
            }
            // generate border
            if (!m_MapData->IsTilesEmpty(mapIndex) &&
                m_MapData->GetTileBack(mapIndex)->GetTile().type != 102) {
                for (auto &dir : direction) {
                    tmpMapIndex = j + dir.x + (i + dir.y) * m_Size.x;
                    if (i + dir.y >= 0 && i + dir.y < m_Size.y &&
                        j + dir.x >= 0 && j + dir.x < m_Size.x &&
                        m_MapData->IsTilesEmpty(tmpMapIndex)) {
                        m_MapData->AddTile(
                            tmpMapIndex,
                            TileFactory::CreateTile(s_Tile{
                                j + dir.x + m_Level->GetLevelIndexMin().x - 1,
                                i + dir.y + m_Level->GetLevelIndexMin().y - 1,
                                102, 0, 0, 0}));
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
            if ((1 + i >= m_Size.y) ||
                (1 + i >= 0 && m_MapData->IsTilesEmpty(mapIndex + m_Size.x))) {
                m_MapData->GetTileBack(mapIndex)->SetCloseDisplayB24(true);
            }
        }
    }

    for (auto &tile : m_MapData->GetTilesQueue()) {
        m_Children.push_back(tile);
    }
}

void Map::LoadEnemy() {
    m_MapData->ClearEnemies();

    std::size_t mapIndex = 0;
    for (auto &enemy : m_Level->GetEnemies()) {
        mapIndex = GamePostion2MapIndex({enemy.x, enemy.y});
        m_MapData->AddEnemy(mapIndex,
                            EnemyFactory::CreateEnemy(enemy, m_MapData));
    }

    for (auto &enemy : m_MapData->GetEnemyQueue()) {
        m_Children.push_back(enemy);
    }
}

std::size_t Map::GetLevelNum() const {
    return m_LevelNum;
}

bool Map::CheckShowPosition(const glm::vec2 &position1,
                            const glm::vec2 &position2) {
    return (position1.x >= position2.x - (ALLOW_EXTRA_DRAW + HalfColNumber) &&
            position1.x <= position2.x + (ALLOW_EXTRA_DRAW + HalfColNumber) &&
            position1.y >= position2.y - (ALLOW_EXTRA_DRAW + HalfRowNumber) &&
            position1.y <= position2.y + (ALLOW_EXTRA_DRAW + HalfRowNumber));
}

void Map::CameraUpdate() {
    glm::vec2 cameraPos = m_MainCharacter->GetGamePosition();
    m_Transform.translation = {0, 0};

    for (auto &tile : m_MapData->GetTilesQueue()) {
        if (tile->GetTile().x == 0 && tile->GetTile().y == 0) {
            tile->SetOverlay(true);
        }
        if (CheckShowPosition({tile->GetTile().x, tile->GetTile().y},
                              cameraPos)) {
            tile->SetVisible(true);
            if (CanPlayerSeePosition({tile->GetTile().x, tile->GetTile().y})) {
                tile->SetOverlay(false);
            }
            else {
                tile->SetOverlay(true);
            }
        }
        else {
            tile->SetVisible(false);
        }
    }
    for (auto &enemy : m_MapData->GetEnemyQueue()) {
        if (CheckShowPosition(enemy->GetGamePosition(), cameraPos)) {
            enemy->SetVisible(true);
            if (CanPlayerSeePosition(enemy->GetGamePosition())) {
                enemy->SetShadow(false);
            }
            else {
                enemy->SetShadow(true);
            }
        }
        else {
            enemy->SetVisible(false);
        }
    }
}

void Map::TempoUpdate() {
    if (!m_PlayerTrigger) {
        m_MapData->SetPlayerPosition(m_MainCharacter->GetGamePosition());
        m_TempoAttack = false;
        for (auto &enemy : m_MapData->GetEnemyQueue()) {
            enemy->TempoMove();
        }
        m_ShadowRenderDP.clear();
        m_ShadowRenderDP.resize(m_Size.x * m_Size.y, false);
    }
    m_PlayerTrigger = false;
}

void Map::PlayerTrigger() {
    m_PlayerTrigger = false;
    TempoUpdate();
    m_PlayerTrigger = true;
}

void Map::TempoTrigger() {
    TempoUpdate();
}

void Map::Update() {
    std::size_t mapIndex = 0;
    CameraUpdate();
    m_MiniMap->Update();
    std::vector<std::shared_ptr<Enemy>> EnemyQueue(m_MapData->GetEnemyQueue());
    for (auto &enemy : EnemyQueue) {
        if (!enemy->GetSeen()) {
            continue;
        }
        if (enemy->GetCanMove()) {
            mapIndex = GamePostion2MapIndex(enemy->GetGamePosition());

            m_MapData->RemoveEnemy(mapIndex);
            m_MapData->AddEnemy(
                GamePostion2MapIndex(enemy->GetWillMovePosition()), enemy);
        }
        enemy->Update();

        EnemyAttackHandle(enemy);
    }
}

std::size_t Map::GamePostion2MapIndex(const glm::ivec2 &position) const {
    return (position.x - m_Level->GetLevelIndexMin().x + 1) +
           (position.y - m_Level->GetLevelIndexMin().y + 1) * m_Size.x;
}

std::shared_ptr<MapData> Map::GetMapData() const {
    return m_MapData;
}

bool Map::isVaildPosition(const glm::ivec2 &position) {
    if (position.x < m_Level->GetLevelIndexMin().x ||
        position.x > m_Level->GetLevelIndexMax().x ||
        position.y < m_Level->GetLevelIndexMin().y ||
        position.y > m_Level->GetLevelIndexMax().y) {
        return false;
    }
    return true;
}

bool Map::isVaildMove(const glm::ivec2 &position) {
    std::size_t mapIndex = GamePostion2MapIndex(position);
    if (m_MapData->IsTilesEmpty(mapIndex)) {
        return false;
    }
    if (m_MapData->GetTileBack(mapIndex)->IsWall()) {
        return false;
    }
    return true;
}

void Map::RemoveEnemy(const std::size_t position) {
    m_Children.erase(std::remove(m_Children.begin(), m_Children.end(),
                                 m_MapData->GetEnemy(position)),
                     m_Children.end());
    m_MapData->RemoveEnemy(position);
}

void Map::RemoveWall(const std::size_t position) {
    auto tile = m_MapData->GetTileBack(position)->GetTile();

    if (tile.type == 102) {
        return;
    }
    m_Children.erase(std::remove(m_Children.begin(), m_Children.end(),
                                 m_MapData->GetTileBack(position)),
                     m_Children.end());
    m_MapData->RemoveTile(position, m_MapData->GetTileBack(position));
    m_MapData->AddTile(
        position, TileFactory::CreateTile(s_Tile{tile.x, tile.y, 0, tile.zone,
                                                 tile.torch, tile.cracked}));
    m_Children.push_back(m_MapData->GetTileBack(position));
}

void Map::OpenDoor(const std::size_t position) {
    auto tile = m_MapData->GetTileBack(position)->GetTile();
    auto doorType = tile.type;
    auto gamePosition = glm::vec2(tile.x, tile.y);

    if (doorType == 50 || doorType == 103 || doorType == 118) {
        for (size_t i = 0; i < 4; i++) {
            auto tmpPosition = gamePosition + m_EnemyMove[i];
            auto tmpMapIndex = GamePostion2MapIndex(tmpPosition);
            if (m_MapData->IsPositionDoor(tmpPosition) &&
                doorType ==
                    m_MapData->GetTileBack(tmpMapIndex)->GetTile().type) {
                m_Children.erase(
                    std::remove(m_Children.begin(), m_Children.end(),
                                m_MapData->GetTileBack(tmpMapIndex)),
                    m_Children.end());
                m_MapData->RemoveTile(tmpMapIndex,
                                      m_MapData->GetTileBack(tmpMapIndex));
            }
        }
        m_Children.erase(std::remove(m_Children.begin(), m_Children.end(),
                                     m_MapData->GetTileBack(position)),
                         m_Children.end());
        m_MapData->RemoveTile(position, m_MapData->GetTileBack(position));
    }
}

void Map::EnemyAttackHandle(const std::shared_ptr<Enemy> &enemy) {
    if (m_OverlayRedTime + 200 < Util::Time::GetElapsedTimeMs()) {
        m_OverlayRed = false;
    }
    if (enemy->DidAttack() && !m_TempoAttack) {
        m_TempoAttack = true;
        m_OverlayRed = true;

        m_MainCharacter->lostHP(enemy->GetDamage());
        m_Camera->Shake(100, 10);
        m_OverlayRedTime = Util::Time::GetElapsedTimeMs();
    }
}

bool Map::CanPlayerSeePosition(const glm::vec2 &position) {
    std::size_t mapIndex = m_MapData->GamePosition2MapIndex(position);
    if (m_ShadowRenderDP[mapIndex]) {
        return true;
    }

    // Linear Interpolation
    glm::vec2 playerPosition = m_MainCharacter->GetGamePosition();
    glm::vec2 direction = position - playerPosition;
    if (direction.x > 0) {
        direction.x -= 0.5;
    }
    else if (direction.x < 0) {
        direction.x += 0.5;
    }
    if (direction.y > 0) {
        direction.y -= 0.5;
    }
    else if (direction.y < 0) {
        direction.y += 0.5;
    }
    float distance = glm::length(direction);
    for (float i = 0; i <= 1.0; i += 1.0 / distance) {
        glm::vec2 checkPosition = playerPosition + direction * i;
        checkPosition = {std::round(checkPosition.x),
                         std::round(checkPosition.y)};
        mapIndex = m_MapData->GamePosition2MapIndex(checkPosition);

        if (position == checkPosition) {
            m_ShadowRenderDP[mapIndex] = true;
            return true;
        }
        if (m_MapData->IsPositionWall(checkPosition) ||
            m_MapData->IsPositionDoor(checkPosition)) {
            m_ShadowRenderDP[mapIndex] = false;
            return false;
        }
    }
    return true;
}

} // namespace Dungeon
