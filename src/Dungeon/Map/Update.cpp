#include "Dungeon/Map.h"

#include "Dungeon/Enemy.h"
#include "Util/Logger.hpp"

namespace Dungeon {
void Map::CameraUpdate() {
    glm::vec2 cameraPos = m_MapData->GetPlayerPosition();

    for (auto& tile : m_MapData->GetUnsortedTiles()) {
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
    for (auto& enemy : m_MapData->GetUnsortedEnemies()) {
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
    for (auto& enemy : m_MapData->GetEnemyQueue()) {
        enemy->TempoMove();
    }
    if (isPlayer) {
        m_ShadowRenderDP.clear();
        m_ShadowRenderDP.resize(m_Size.x * m_Size.y, false);
    }
    Update();
}

void Map::PlayerTrigger() {
    m_TempoIndex++;
    TempoUpdate(true);
}

void Map::TempoTrigger(const std::size_t index) {
    if (m_TempoIndex == index) { return; }
    m_TempoIndex = index;
    TempoUpdate(false);
}

void Map::Update() {
    m_Transform.translation = m_MapData->GetPlayer()->GetTranslation();

    if (m_OverlayRedTime + 200 < Util::Time::GetElapsedTimeMs()) {
        m_OverlayRed = false;
    }

    Event::EventQueue.dispatch(this, EventArgs(EventType::DrawableUpdate));
}
}  // namespace Dungeon
