//
// Created by adven on 2024/5/10.
//

#include <typeinfo>
#include "App.hpp"

#include "Util/Logger.hpp"
#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

#include <Util/Input.hpp>
#include <algorithm>
#include "Actions.h"
#include "Dungeon/Enemy.h"
#include "Event/Event.h"
#include "Game/Systems/HandItem.h"
#include "Hash.h"
#include "Helper.hpp"
#include "Music/Player.h"
#include "Music/Tempo.h"
#include "Systems/HEIS.h"
#include "Systems/HandThrow.h"

struct ClickEventType {
    std::vector<Util::Keycode> code;
    std::function<void()>      fptr;
};

using CET = ClickEventType;
static std::size_t BOSS_DEAD = false;

auto musicTime = []() {
    return static_cast<std::size_t>(Music::Player::GetMusicTime() * 1000)
           % static_cast<std::size_t>(Music::Player::GetMusicLength() * 1000);
};

void App::ClickEvent() {
    /**
     * @details Use to test functional.
     */
    m_EventHandler.AddEvent(
        [this]() { LOG_DEBUG(m_DungeonMap->GetMapData()->IsBossDead()); },
        Util::Keycode::T
    );

    /**
     * @details When the player move, detect how to hand item if exist.
     */
    m_EventHandler.AddEvent(
        [this]() {
            const auto [playerGP, playerMI] = Settings::Helper::GetPlayerPosDM(
            );

            Player::Direction direction;
            std::for_each(
                m_MapTableCodeDire.begin(),
                m_MapTableCodeDire.end(),
                [&direction](const auto& elem) {
                    if (Util::Input::IsKeyDown(elem.first)) {
                        direction = elem.second;
                    }
                }
            );

            const auto value = Settings::Helper::Direct2MI(direction);
            const auto nextPos = Settings::Helper::GamePosToMapIdx(
                value + static_cast<glm::ivec2>(playerGP)
            );

            if (!m_DungeonMap->GetMapData()->IsItemEmpty(nextPos)) {
                Game::Systems::HandItem hi(m_DungeonMap, m_MainCharacter);
                hi.DispatchByMI(
                    m_DungeonMap->GetMapData()->GetItem(nextPos),
                    nextPos
                );
            }
        },
        Util::Keycode::W,
        Util::Keycode::D,
        Util::Keycode::S,
        Util::Keycode::A
    );

    /**
     * @details The Player throw out the weapon.
     */
    m_EventHandler.AddEvent(
        [this]() {
            if (!m_ThrowMode
                || !Music::Tempo::IsTempoInRange(
                    500,
                    musicTime(),
                    Music::Player::LoopCounter()
                )) {
                return;
            }

            std::for_each(
                m_MapTableCodeDire.begin(),
                m_MapTableCodeDire.end(),
                [](const auto& elem) {
                    if (!Util::Input::IsKeyDown(elem.first)) { return; }
                    const auto& imagePath = m_MainCharacter->GetToolMod()
                                                ->GetWeapon()
                                                ->GetImagePath();

                    Game::Systems::HandThrow hpma(m_DungeonMap.get());
                    hpma.Dispatch(
                        m_MainCharacter->GetToolMod()->GetWeapon()->GetType(),
                        elem.second,
                        imagePath
                    );
                }
            );

            const auto state = m_MainCharacter->GetToolMod()->GetWeapon();
            if (!state) { LOG_INFO("TEST"); }
            m_MainCharacter->GetToolMod()->DisappearTool(
                false,
                "WEAPON",
                m_MainCharacter->GetToolMod()->GetWeapon()->GetType()
            );

            m_ThrowMode = false;
            m_MainCharacter
                ->MoveByTime(200, m_AniPlayerDestination, m_PlayerMoveDirect);
            m_MainCharacter->Update();
            m_Camera->MoveByTime(200, m_AniCameraDestination);
            m_DungeonMap->PlayerTrigger();
        },
        Util::Keycode::W,
        Util::Keycode::D,
        Util::Keycode::S,
        Util::Keycode::A
    );

    /**
     * @details Prepare to throw out weapon.
     */
    m_EventHandler.AddEvent(
        []() {
            LOG_INFO("Throw Mode");
            m_MainCharacter->PrepareThrowOut(true);
            m_ThrowMode = true;
        },
        {Util::Keycode::UP, Util::Keycode::DOWN}
    );

    /**
     * @details To Next Level
     */
    m_EventHandler.AddEvent(
        [this]() {
            Music::Player::PlayMusic(m_MusicList.back().data(), true);
            Music::Tempo::ReadTempoFile(m_TempoList.back().data());
            m_MusicList.pop_back();
            m_TempoList.pop_back();
            m_DungeonMap->LoadLevel(
                m_DungeonMap->GetLevelNum() + 1,
                m_MainCharacter
            );
            m_AniCameraDestination = {0, 0};
            m_AniPlayerDestination = {0, 0};
        },
        Util::Keycode::N
    );

    /**
     * @details Exit the Game
     */
    m_EventHandler.AddEvent(
        [this]() { m_CurrentState = State::END; },
        Util::Keycode::ESCAPE
    );

    /**
     * @details Move the player
     */
    m_EventHandler.AddEvent(
        [this]() {
            if (m_ThrowMode
                || !Music::Tempo::IsTempoInRange(
                    500,
                    musicTime(),
                    Music::Player::LoopCounter()
                )) {
                return;
            }

            glm::vec2 playerDestination = m_MainCharacter->GetGamePosition();

            if (m_PlayerMoveDirect != Player::NONE) {
                m_PlayerMoveDirect = Player::NONE;
            }
            const std::vector<Util::Keycode> key = {
              Util::Keycode::W,
              Util::Keycode::A,
              Util::Keycode::S,
              Util::Keycode::D
            };
            const std::vector<glm::vec2> direction =
                {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
            const std::vector<Player::Direction> playerDirection = {
              Player::Direction::UP,
              Player::Direction::LEFT,
              Player::Direction::DOWN,
              Player::Direction::RIGHT
            };
            const std::vector<glm::vec2> aniPlayerDirection = {
              {0, DUNGEON_TILE_WIDTH * DUNGEON_SCALE},
              {-DUNGEON_TILE_WIDTH * DUNGEON_SCALE, 0},
              {0, -DUNGEON_TILE_WIDTH * DUNGEON_SCALE},
              {DUNGEON_TILE_WIDTH * DUNGEON_SCALE, 0}
            };
            const std::vector<glm::vec2> aniCameraDirection = {
              {0, -DUNGEON_TILE_WIDTH * DUNGEON_SCALE},
              {DUNGEON_TILE_WIDTH * DUNGEON_SCALE, 0},
              {0, DUNGEON_TILE_WIDTH * DUNGEON_SCALE},
              {-DUNGEON_TILE_WIDTH * DUNGEON_SCALE, 0}
            };

            auto mapIndex = m_DungeonMap->GamePostion2MapIndex(playerDestination
            );
            if (m_DungeonMap->GetMapData()->IsEnemyEmpty(mapIndex)) {
                m_DungeonMap->GetMapData()->GetEnemy(mapIndex)->Struck(2);
                m_Camera->Shake(150, 10);
                m_PlayerMoveDirect = Player::UP;

            } else {
                for (std::size_t i = 0; i < 4; i++) {
                    if (Util::Input::IsKeyDown(key[i])) {
                        // origin mapdata actions
                        playerDestination = m_MainCharacter->GetGamePosition()
                                            + direction[i];
                        m_MainCharacter->SetFaceTo(playerDirection[i]);
                        auto mapIndex = m_DungeonMap->GamePostion2MapIndex(
                            playerDestination
                        );
                        if (m_DungeonMap->GetMapData()->IsPositionInteractive(
                                playerDestination
                            )) {
                            if (m_DungeonMap->GetMapData()->IsEnemyEmpty(
                                    mapIndex
                                )) {
                                m_DungeonMap->GetMapData()
                                    ->GetEnemy(mapIndex)
                                    ->Struck(2);

                                m_Camera->Shake(150, 10);
                            } else if (m_DungeonMap->GetMapData()
                                           ->IsPositionWall(playerDestination
                                           )) {
                                m_DungeonMap->RemoveWall(
                                    m_DungeonMap->GamePostion2MapIndex(
                                        playerDestination
                                    )
                                );
                            } else if (m_DungeonMap->GetMapData()
                                           ->IsPositionDoor(playerDestination
                                           )) {
                                m_DungeonMap->OpenDoor(
                                    m_DungeonMap->GamePostion2MapIndex(
                                        playerDestination
                                    )
                                );
                                m_Camera->Shake(100, 10);
                            }
                        } else {
                            m_PlayerMoveDirect = playerDirection[i];

                            m_AniPlayerDestination = {
                              m_AniPlayerDestination.x
                                  + aniPlayerDirection[i].x,
                              m_AniPlayerDestination.y + aniPlayerDirection[i].y
                            };
                            m_AniCameraDestination = {
                              m_AniCameraDestination.x
                                  + aniCameraDirection[i].x,
                              m_AniCameraDestination.y + aniCameraDirection[i].y
                            };
                        }
                    }
                }
            }
            m_MainCharacter
                ->MoveByTime(200, m_AniPlayerDestination, m_PlayerMoveDirect);
            m_MainCharacter->Update();
            Event::EventQueue.dispatch(
                m_MainCharacter.get(),
                EventArgs(EventType::PlayerMove)
            );
            m_Camera->MoveByTime(200, m_AniCameraDestination);
            m_DungeonMap->PlayerTrigger();
        },
        Util::Keycode::W,
        Util::Keycode::D,
        Util::Keycode::S,
        Util::Keycode::A
    );

    m_EventHandler.AddEvent(
        [this]() {
            const auto tile = m_DungeonMap->GetMapData()->GetTile(
                m_DungeonMap->GamePostion2MapIndex(
                    m_MainCharacter->GetGamePosition()
                )
            );

            // LOG_INFO(tile->GetTile().type);
            if (tile->GetTile().type == 9
                && m_DungeonMap->GetMapData()->IsBossDead()) {
                Music::Player::PlayMusic(m_MusicList.back().data(), true);
                Music::Tempo::ReadTempoFile(m_TempoList.back().data());
                m_MusicList.pop_back();
                m_TempoList.pop_back();
                m_DungeonMap->LoadLevel(m_DungeonMap->GetLevelNum() + 1, m_MainCharacter);
                m_AniCameraDestination = {0, 0};
                m_AniPlayerDestination = {0, 0};
            }
        },
        Util::Keycode::W,
        Util::Keycode::D,
        Util::Keycode::S,
        Util::Keycode::A
    );

    //    m_EventHandler.AddEvent({Util::Keycode::W}, ThrowWeapon);
};
