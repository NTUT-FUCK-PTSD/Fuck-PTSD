#include "Dungeon/Map.h"

namespace Dungeon {
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

    Event::Dispatcher.dispatch(
        EventType::DrawableUpdate,
        this,
        EventArgs(EventType::DrawableUpdate)
    );
}
}  // namespace Dungeon
