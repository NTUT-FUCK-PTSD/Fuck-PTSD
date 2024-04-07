#include "Dungeon/Map.h"

#include "Dungeon/EnemyFactory.h"

namespace Dungeon {

Map::Map(const std::shared_ptr<Player> &mainCharacter, const std::string &path,
         const int &levelNum)
    : m_MainCharacter(mainCharacter) {
    m_Level = std::make_unique<Level>(path, levelNum);

    m_Size = m_Level->GetLevelIndexMax() - m_Level->GetLevelIndexMin() +
             3; // add 3 for the border
    m_MapData = std::make_shared<MapData>(m_Level->GetLevelIndexMin(),
                                          m_Level->GetLevelIndexMax(), m_Size);
    m_MapData->SetPlayerPosition(m_MainCharacter->GetGamePosition());
    size_t mapIndex = 0, tmpMapIndex = 0;

    for (auto &tile : m_Level->GetTiles()) {
        mapIndex = GamePostion2MapIndex({tile.x, tile.y});
        if (tile.type == 23 || tile.type == 24 || tile.type == 103 ||
            tile.type == 106 || tile.type == 111 || tile.type == 118) {
            m_MapData->AddTile(mapIndex, std::make_shared<Tile>(s_Tile{
                                             tile.x, tile.y, 0, tile.zone,
                                             tile.torch, tile.cracked}));
            m_Tiles.push_back(m_MapData->GetTileBack(mapIndex));
        }
        m_MapData->AddTile(mapIndex, std::make_shared<Tile>(tile));
        m_Tiles.push_back(m_MapData->GetTileBack(mapIndex));
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
                        !m_MapData->IsTilesEmpty(tmpMapIndex) &&
                        (m_MapData->GetTileBack(tmpMapIndex)->IsWall())) {
                        doorCount++;
                    }
                }
                if (doorCount >= 2) {
                    m_MapData->PopBackTile(mapIndex);
                    m_Tiles.erase(
                        std::remove(m_Tiles.begin(), m_Tiles.end(), tmp),
                        m_Tiles.end()); // Remove Child
                    if (tmp->GetTile().type == 111) {
                        m_MapData->AddTile(
                            mapIndex,
                            std::make_shared<Tile>(s_Tile{
                                tmp->GetTile().x, tmp->GetTile().y, 52,
                                tmp->GetTile().zone, tmp->GetTile().torch,
                                tmp->GetTile().cracked}));
                    }
                    else {
                        if (tmp->GetTile().type == 103 ||
                            tmp->GetTile().type == 118) {
                            m_MapData->AddTile(
                                mapIndex,
                                std::make_shared<Tile>(s_Tile{
                                    tmp->GetTile().x, tmp->GetTile().y, 50,
                                    tmp->GetTile().zone, tmp->GetTile().torch,
                                    tmp->GetTile().cracked}));
                        }
                        else {
                            m_MapData->AddTile(
                                mapIndex,
                                std::make_shared<Tile>(s_Tile{
                                    tmp->GetTile().x, tmp->GetTile().y, 51,
                                    tmp->GetTile().zone, tmp->GetTile().torch,
                                    tmp->GetTile().cracked}));
                        }
                    }
                    m_Tiles.push_back(m_MapData->GetTileBack(mapIndex));
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
                            std::make_shared<Tile>(s_Tile{
                                j + dir.x + m_Level->GetLevelIndexMin().x - 1,
                                i + dir.y + m_Level->GetLevelIndexMin().y - 1,
                                102, 0, 0, 0}));
                        m_Tiles.push_back(m_MapData->GetTileBack(tmpMapIndex));
                    }
                }
            }
        }
    }

    // SetCloseDisplayb24
    for (int i = 0; i < m_Size.y; i++) {
        for (int j = 0; j < m_Size.x; j++) {
            mapIndex = j + i * m_Size.x;
            if (m_MapData->IsTilesEmpty(mapIndex)) {
                continue;
            }
            if ((1 + i >= m_Size.y) ||
                (1 + i >= 0 && m_MapData->IsTilesEmpty(mapIndex + m_Size.x))) {
                m_MapData->GetTileBack(mapIndex)->SetCloseDisplayb24(true);
            }
        }
    }

    for (auto &enemy : m_Level->GetEnemies()) {
        mapIndex = GamePostion2MapIndex({enemy.x, enemy.y});
        m_MapData->AddEnemy(mapIndex,
                            EnemyFactory::CreateEnemy(enemy, m_MapData));
        m_Enemies.push_back(m_MapData->GetEnemy(mapIndex));
    }

    // Add testing
    mapIndex = GamePostion2MapIndex({1, 1});
    auto enemy = EnemyFactory::CreateEnemy(s_Enemy{1, 1, 11, 0, 0}, m_MapData);
    m_MapData->AddEnemy(mapIndex, enemy);
    m_Enemies.push_back(m_MapData->GetEnemy(mapIndex));

    for (auto &tile : m_Tiles) {
        m_Children.push_back(tile);
    }
    for (auto &enemy : m_Enemies) {
        m_Children.push_back(enemy);
    }
    CameraUpdate();
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

    for (auto &tile : m_Tiles) {
        if (CheckShowPosition({tile->GetTile().x, tile->GetTile().y},
                              cameraPos)) {
            tile->SetVisible(true);
        }
        else {
            tile->SetVisible(false);
        }
    }
    for (auto &enemy : m_Enemies) {
        if (CheckShowPosition(enemy->GetGamePosition(), cameraPos)) {
            enemy->SetVisible(true);
        }
        else {
            enemy->SetVisible(false);
        }
    }
}

void Map::TempoUpdate() {
    m_MapData->SetPlayerPosition(m_MainCharacter->GetGamePosition());
    for (auto &enemy : m_Enemies) {
        enemy->TempoMove();
    }
}

void Map::Update() {
    size_t mapIndex = 0;
    CameraUpdate();
    for (auto &enemy : m_Enemies) {
        if (!enemy->GetVisible()) {
            continue;
        }
        if (enemy->GetCanMove()) {
            mapIndex = GamePostion2MapIndex(enemy->GetGamePosition());

            m_MapData->RemoveEnemy(mapIndex);
            m_MapData->AddEnemy(
                GamePostion2MapIndex(enemy->GetWillMovePosition()), enemy);
        }
        enemy->Update();
    }
}

size_t Map::GamePostion2MapIndex(const glm::ivec2 &position) const {
    return (position.x - m_Level->GetLevelIndexMin().x + 1) +
           (position.y - m_Level->GetLevelIndexMin().y + 1) * m_Size.x;
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
    size_t mapIndex = GamePostion2MapIndex(position);
    if (m_MapData->IsTilesEmpty(mapIndex)) {
        return false;
    }
    if (m_MapData->GetTileBack(mapIndex)->IsWall()) {
        return false;
    }
    return true;
}

} // namespace Dungeon
