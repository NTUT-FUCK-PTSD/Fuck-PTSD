#include "Event/Event.h"
#include "Dungeon/Map.h"

#include "Dungeon/Enemy.h"
#include "Event/EventArgs.h"
#include "Game/Player.h"
#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

namespace Dungeon {
void Map::InitEvent() {
    m_Event.appendListener(
        EventType::AttackPlayer,
        [this](const Object*, const EventArgs&) {
            if (Event::GetAttackPlayer()) {
                m_Camera->Shake(100, 10);
                m_OverlayRed = true;
                m_OverlayRedTime = Util::Time::GetElapsedTimeMs();
            }
        }
    );

    m_Event.appendListener(
        EventType::EnemyMove,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<
                void(const Enemy*, const EnemyMoveEventArgs&)>(
                [this](const Enemy* sender, const EnemyMoveEventArgs& e) {
                    // Notice sender is const Enemy* but we need to modify it
                    auto fromMapIndex = GamePostion2MapIndex(
                        sender->GetGamePosition()
                    );
                    auto toMapIndex = e.GetMapIndex();
                    auto enemy = m_MapData->GetEnemy(fromMapIndex);
                    auto toGamePosition = MapIndex2GamePosition(toMapIndex);

                    enemy->SetGamePosition(toGamePosition);
                    m_MapData->MoveEnemy(fromMapIndex, toMapIndex);
                    if (CheckShowPosition(
                            toGamePosition,
                            m_MapData->GetPlayerPosition()
                        )) {
                        enemy->SetCameraUpdate(true);
                        if (CanPlayerSeePosition(toGamePosition)) {
                            enemy->SetShadow(false);
                        } else {
                            enemy->SetShadow(true);
                        }
                    }
                    m_MiniMap->UpdateCubeColor(fromMapIndex);
                    m_MiniMap->UpdateCubeColor(toMapIndex);
                }
            ),
            [](const Object*, const EventArgs& e) {
                return dynamic_cast<const EnemyMoveEventArgs*>(&e) != nullptr;
            }
        )
    );

    m_Event.appendListener(
        EventType::PlayerMove,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<void(const Player*, const EventArgs&)>(
                [this](const Player* sender, const EventArgs&) {
                    PlayerMove(sender->GetGamePosition());
                    CameraUpdate();
                }
            ),
            [](const Object* sender, const EventArgs&) {
                return dynamic_cast<const Player*>(sender) != nullptr;
            }
        )
    );

    m_Event.appendListener(
        EventType::ResetMap,
        [this](const Object*, const EventArgs&) {
            m_Children.clear();
            if (m_MapData) {
                m_MapData->ClearTiles();
                m_MapData->ClearEnemies();
            }
            if (m_MiniMap) {
                m_Camera->RemoveUIChild(m_MiniMap);
            }

            m_Camera->SetPosition({0, 0});
        }
    );
}
}  // namespace Dungeon
