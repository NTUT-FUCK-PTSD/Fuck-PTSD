#include "Dungeon/Map.h"

#include "ToolBoxs.h"
#include "Util/Logger.hpp"
#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

#include "Dungeon/Enemy.h"
#include "Dungeon/TileFactory.h"
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
                [this](const Player* player, const EventArgs&) {
                    if (m_BossRoom == 1) {
                        if (player->GetGamePosition().y <= -7) {
                            auto mapIndex = GamePostion2MapIndex(
                                glm::ivec2(-1, -6)
                            );
                            for (int i = 0; i < 3; i++) {
                                m_TileHead->RemoveChild(
                                    m_MapData->GetTile(mapIndex + i)
                                );
                                m_MapData->RemoveTile(mapIndex + i);
                                m_MapData->AddTile(
                                    mapIndex + i,
                                    TileFactory::CreateTile(
                                        s_Tile{-1 + i, -6, 109, 5, 0, 0}
                                    )
                                );
                                m_TileHead->AddChild(
                                    m_MapData->GetTile(mapIndex + i)
                                );
                            }
                            mapIndex = GamePostion2MapIndex(glm::ivec2(-2, -5));
                            for (int i = 0; i < 5; i++) {
                                m_TileHead->RemoveChild(
                                    m_MapData->GetTile(mapIndex + i)
                                );
                                m_MapData->RemoveTile(mapIndex + i);
                                m_MapData->AddTile(
                                    mapIndex + i,
                                    TileFactory::CreateTile(
                                        s_Tile{-2 + i, -5, 102, 5, 0, 0}
                                    )
                                );
                                m_TileHead->AddChild(
                                    m_MapData->GetTile(mapIndex + i)
                                );
                            }
                            LOG_INFO("King Conga Room");
                            m_BossRoom = 2;
                        }
                    }
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
            if (m_MapData) {
                m_TileHead->ClearChildren();
                m_EnemyHead->ClearChildren();
                m_ItemHead->ClearChildren();
                m_MapData.reset();
            }
            if (m_MiniMap) { m_Camera->RemoveUIChild(m_MiniMap); }
            m_BossRoom = 0;
            m_Camera->SetPosition({0, 0});
        }
    );

    m_Event.appendListener(
        EventType::EnemyRemove,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<
                void(const Object*, const EnemyRemoveEventArgs&)>(
                [this](const Object*, const EnemyRemoveEventArgs& e) {
                    auto enemy = m_MapData->GetEnemy(e.GetMapIndex());
                    if (m_BossRoom > 0) {
                        if (enemy->IsBoss()) {
                            auto mapIndex = GamePostion2MapIndex(
                                glm::ivec2(-2, -18)
                            );
                            for (int i = 0; i < 5; i++) {
                                m_TileHead->RemoveChild(
                                    m_MapData->GetTile(mapIndex + i)
                                );
                                m_MapData->RemoveTile(mapIndex + i);
                                m_MapData->AddTile(
                                    mapIndex + i,
                                    TileFactory::CreateTile(
                                        s_Tile{-2 + i, -18, 0, 5, 0, 0}
                                    )
                                );
                                m_TileHead->AddChild(
                                    m_MapData->GetTile(mapIndex + i)
                                );
                            }
                            CameraUpdate();
                        }
                    }
                    const auto&& enemyCoin = enemy->GetCoin();
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

    m_Event.appendListener(
        EventType::WallRemove,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<
                void(const Object*, const WallRemoveEventArgs&)>(
                [this](const Object*, const WallRemoveEventArgs& e) {
                    RemoveWall(e.GetMapIndex());
                }
            ),
            [](const Object*, const EventArgs& e) {
                return dynamic_cast<const WallRemoveEventArgs*>(&e) != nullptr;
            }
        )
    );
}
}  // namespace Dungeon
