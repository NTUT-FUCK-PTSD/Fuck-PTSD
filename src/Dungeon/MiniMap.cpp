#include "Dungeon/MiniMap.h"

namespace Dungeon {
MiniMap::MiniMap(std::shared_ptr<MapData> mapData)
    : m_MapData(mapData) {
    BuildMiniMap();
    Update();
}

void MiniMap::BuildMiniMap() {
    m_ColorCubes.clear();
    m_Children.clear();
    std::size_t mapIndex = 0;
    for (int i = 0; i < m_MapData->GetSize().y; i++) {
        for (int j = 0; j < m_MapData->GetSize().x; j++) {
            mapIndex = j + i * m_MapData->GetSize().x;
            m_ColorCubes.push_back(std::make_shared<ColorCube>());
            m_Children.push_back(std::make_shared<Util::GameObject>(
                m_ColorCubes.back(), 100 - (1e-1)));
            m_Children[mapIndex]->SetVisible(true);
            m_Children[mapIndex]->m_Transform.scale = {m_Scale, m_Scale};
            m_Children[mapIndex]->m_Transform.translation = {
                static_cast<int>(WINDOW_WIDTH) / 2 - DUNGEON_TILE_WIDTH -
                    (2 * (m_MapData->GetSize().x - (j + 1))) * m_Scale,
                -(static_cast<int>(WINDOW_HEIGHT) / 2) +
                    (52 * DUNGEON_SCALE + DUNGEON_TILE_WIDTH) +
                    (2 * (m_MapData->GetSize().y - (i + 1))) * m_Scale};
            UpdateTileColor(mapIndex);
            m_Children[mapIndex]->SetVisible(false);
        }
    }
}

void MiniMap::UpdateTileColor(const std::size_t mapIndex) {
    if (!m_MapData->IsTilesEmpty(mapIndex)) {
        if (m_MapData->GetTileBack(mapIndex)->IsWall()) {
            if (m_MapData->GetTileBack(mapIndex)->GetTile().type == 102) {
                m_ColorCubes[mapIndex]->SetColor(CubeColor::gray);
            }
            else if (m_MapData->GetTileBack(mapIndex)->GetTile().type == 107) {
                m_ColorCubes[mapIndex]->SetColor(CubeColor::stone);
            }
            else if (m_MapData->GetTileBack(mapIndex)->GetTile().type == 104 ||
                     m_MapData->GetTileBack(mapIndex)->GetTile().type == 105 ||
                     m_MapData->GetTileBack(mapIndex)->GetTile().type == 110) {
                m_ColorCubes[mapIndex]->SetColor(CubeColor::metrognome);
            }
            else {
                m_ColorCubes[mapIndex]->SetColor(CubeColor::wall);
            }
        }
        else if (m_MapData->GetTileBack(mapIndex)->IsDoor()) {
            m_ColorCubes[mapIndex]->SetColor(CubeColor::green);
        }
        else {
            m_ColorCubes[mapIndex]->SetColor(CubeColor::white);
        }
    }
}

void MiniMap::SetColor(const glm::vec2 &position, CubeColor color) {
    auto mapIndex = m_MapData->GamePosition2MapIndex(position);
    m_ColorCubes[mapIndex]->SetColor(color);
    m_Children[mapIndex]->SetVisible(true);
}

void MiniMap::SetVisible(const glm::vec2 &position, bool visible) {
    auto mapIndex = m_MapData->GamePosition2MapIndex(position);
    m_Children[mapIndex]->SetVisible(visible);
}

void MiniMap::SetVisible(const std::size_t position, bool visible) {
    m_Children[position]->SetVisible(visible);
}

void MiniMap::AddChildren(
    const std::vector<std::shared_ptr<GameObject>> &children) {
    m_Children.reserve(m_Children.size() + children.size());
    m_Children.insert(m_Children.end(), children.begin(), children.end());
}

void MiniMap::RemoveChildren(
    const std::vector<std::shared_ptr<GameObject>> &children) {
    for (auto &child : children) {
        RemoveChild(child);
    }
}

void MiniMap::Update() {
    // Update Tiles
    for (int i = 0; i < m_MapData->GetSize().y; i++) {
        for (int j = 0; j < m_MapData->GetSize().x; j++) {
            auto mapIndex = j + i * m_MapData->GetSize().x;
            if (!m_ColorCubes[mapIndex]->GetAvailable()) {
                continue;
            }
            if (!m_MapData->IsTilesEmpty(mapIndex)) {
                if (!m_MapData->GetTileBack(mapIndex)->GetSeen()) {
                    continue;
                }
            }
            else {
                m_Children[mapIndex]->SetVisible(false);
                continue;
            }
            UpdateTileColor(mapIndex);
            m_Children[mapIndex]->SetVisible(true);
        }
    }

    // Update Enemies
    RemoveChildren(m_EnemiesCubeObjects);
    m_EnemiesCubeObjects.clear();
    for (auto &enemy : m_MapData->GetEnemyQueue()) {
        if (!enemy->GetSeen()) {
            continue;
        }
        auto position = enemy->GetGamePosition();
        auto i = position.x - m_MapData->GetLevelIndexMin().x + 1;
        auto j = position.y - m_MapData->GetLevelIndexMin().y + 1;
        auto enemyCube = std::make_shared<ColorCube>();
        m_EnemiesCubeObjects.push_back(
            std::make_shared<Util::GameObject>(enemyCube, 100 - (1e-2)));
        m_EnemiesCubeObjects.back()->SetVisible(true);
        m_EnemiesCubeObjects.back()->m_Transform.scale = {m_Scale, m_Scale};
        m_EnemiesCubeObjects.back()->m_Transform.translation = {
            static_cast<int>(WINDOW_WIDTH) / 2 - DUNGEON_TILE_WIDTH -
                (2 * (m_MapData->GetSize().x - (i + 1))) * m_Scale,
            -(static_cast<int>(WINDOW_HEIGHT) / 2) +
                (52 * DUNGEON_SCALE + DUNGEON_TILE_WIDTH) +
                (2 * (m_MapData->GetSize().y - (j + 1))) * m_Scale};
        enemyCube->SetColor(CubeColor::red);
    }
    AddChildren(m_EnemiesCubeObjects);

    // Update Player
    RemoveChild(m_PlayerCubeObject);
    auto position = m_MapData->GetPlayerPosition();
    auto i = position.x - m_MapData->GetLevelIndexMin().x + 1;
    auto j = position.y - m_MapData->GetLevelIndexMin().y + 1;
    auto playerCube = std::make_shared<ColorCube>();
    m_PlayerCubeObject = std::make_shared<Util::GameObject>(playerCube, 100);
    m_PlayerCubeObject->SetVisible(m_PlayerStatus);
    m_PlayerCubeObject->m_Transform.scale = {m_Scale, m_Scale};
    m_PlayerCubeObject->m_Transform.translation = {
        static_cast<int>(WINDOW_WIDTH) / 2 - DUNGEON_TILE_WIDTH -
            (2 * (m_MapData->GetSize().x - (i + 1))) * m_Scale,
        -(static_cast<int>(WINDOW_HEIGHT) / 2) +
            (52 * DUNGEON_SCALE + DUNGEON_TILE_WIDTH) +
            (2 * (m_MapData->GetSize().y - (j + 1))) * m_Scale};
    playerCube->SetColor(CubeColor::blue);

    if (Util::Time::GetElapsedTimeMs() - m_LastPlayerChanged > 250) {
        m_PlayerStatus = !m_PlayerStatus;
        m_LastPlayerChanged = Util::Time::GetElapsedTimeMs();
    }
    AddChild(m_PlayerCubeObject);
}

void MiniMap::SetScale(double scale) {
    m_Scale = scale;
    BuildMiniMap();
    Update();
}
} // namespace Dungeon
