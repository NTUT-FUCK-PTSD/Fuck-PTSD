#include "Dungeon/Map.h"

#include "ToolBoxs.h"
#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

#include "Dungeon/Enemy.h"
#include "Event/Event.h"
#include "Event/EventArgs.h"
#include "Event/EventType.h"
#include "Game/Graphs/Coin.h"
#include "Game/Player.h"

namespace Dungeon {
void Map::InitEvent() {
    Event::EventQueue.appendListener(
        EventType::AttackPlayer,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<
                void(const Object*, const AttackPlayerEventArgs&)>(
                [this](const Object*, const AttackPlayerEventArgs& e) {
                    if (Event::GetAttackPlayer() && e.GetDamage() > 0) {
                        m_Camera->Shake(100, 10);
                        m_OverlayRed = true;
                        m_OverlayRedTime = Util::Time::GetElapsedTimeMs();
                    }
                }
            ),
            [](const Object*, const EventArgs& e) {
                return dynamic_cast<const AttackPlayerEventArgs*>(&e)
                       != nullptr;
            }
        )
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
                [this](const Player*, const EventArgs&) { CameraUpdate(); }
            ),
            [](const Object* sender, const EventArgs&) {
                return dynamic_cast<const Player*>(sender) != nullptr;
            }
        )
    );

    m_Event.appendListener(
        EventType::ResetMap,
        [this](const Object*, const EventArgs&) {
            if (m_MapData) {
                m_TileHead->ClearChildren();
                m_EnemyHead->ClearChildren();
                m_ItemHead->ClearChildren();
                m_MapData.reset();
            }
            if (m_MiniMap) { m_Camera->RemoveUIChild(m_MiniMap); }

            m_Camera->SetPosition({0, 0});
        }
    );

    m_Event.appendListener(
        EventType::EnemyRemove,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<
                void(const Object*, const EnemyRemoveEventArgs&)>(
                [this](const Object*, const EnemyRemoveEventArgs& e) {
                    const auto&& enemyCoin =
                        m_MapData->GetEnemy(e.GetMapIndex())->GetCoin();
                    RemoveEnemy(e.GetMapIndex());
                    const auto& coin = std::make_shared<Game::Graphs::Coin>(
                        enemyCoin
                    );
                    AddItem(e.GetMapIndex(), coin);
                }
            ),
            [](const Object*, const EventArgs& e) {
                return dynamic_cast<const EnemyRemoveEventArgs*>(&e) != nullptr;
            }
        )
    );
}
}  // namespace Dungeon
