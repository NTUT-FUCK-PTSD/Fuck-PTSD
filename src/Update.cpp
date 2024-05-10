//
// Created by adven on 2024/5/10.
//

#include "App.hpp"

#include "Util/Logger.hpp"
#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

#include <Util/Input.hpp>
#include <algorithm>
#include "Actions.h"
#include "Display/BeatHeart.h"
#include "Display/BeatIndicator.h"
#include "Dungeon/Enemy.h"
#include "Dungeon/MapHandler.h"
#include "Event/Event.h"
#include "Game/Graphs/Spear.h"
#include "Game_config.h"
#include "HPIS.h"
#include "Helper.hpp"
#include "Music/Player.h"
#include "Music/Tempo.h"
#include "System.h"
#include "Systems/HEIS.h"
#include "Systems/HPIS.h"

void App::Update() {
    auto musicTime =
        static_cast<std::size_t>(Music::Player::GetMusicTime() * 1000)
        % static_cast<std::size_t>(Music::Player::GetMusicLength() * 1000);

    m_EventHandler.Update();

    if (Music::Tempo::IsSwitch()) {
        m_DungeonMap->TempoTrigger(Music::Tempo::GetBeatIdx());
        Display::BeatHeart::SwitchHeart(100);
        Event::SetAttackPlayer(true);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::T)) {
        const auto& item = std::make_shared<Game::Graphs::Spear>();
        const auto& size = Settings::Helper::CountImgPixel(
            Players::Config::IMAGE_SPEAR.data(),
            1,
            2
        );
        const auto& item2 = std::make_shared<SpriteSheet>(
            Players::Config::IMAGE_SPEAR.data(),
            size,
            std::vector<std::size_t>{0},
            false,
            100,
            true,
            100
        );
        item->SetDrawable(item2);
        m_DungeonMap->AddItem(414, item);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::N)) {
        m_DungeonMap->LoadLevel(m_DungeonMap->GetLevelNum() + 1);
        m_AniCameraDestination = {0, 0};
        m_AniPlayerDestination = {0, 0};
    }

    if (Util::Input::IsKeyDown(Util::Keycode::UP)
        && Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        m_MainCharacter->PrepareThrowOut(true);
        LOG_INFO("Throw Mode");
        m_ThrowMode = true;
    }

    // player throw weapon
    if (m_ThrowMode
        && (Util::Input::IsKeyDown(Util::Keycode::W)
            || Util::Input::IsKeyDown(Util::Keycode::D)
            || Util::Input::IsKeyDown(Util::Keycode::S)
            || Util::Input::IsKeyDown(Util::Keycode::A))
        && Music::Tempo::IsTempoInRange(
            500,
            musicTime,
            Music::Player::LoopCounter()
        )) {
        m_MainCharacter->PrepareThrowOut(false);
        for (const auto& elem : m_MapTableCodeDire) {
            if (Util::Input::IsKeyDown(elem.first)) {
                std::string imageagePath = "";
                auto        t = m_MainCharacter->GetToolMod()->GetAllTools();
                std::for_each(
                    t.begin(),
                    t.end(),
                    [&imageagePath](const auto& elem) {
                        if (elem->GetImagePath() != "") {
                            imageagePath = elem->GetImagePath();
                        }
                    }
                );
                Game::Actions::ThrowOutWeapon(
                    m_DungeonMap.get(),
                    elem.second,
                    imageagePath
                );
                //                Game::Systems::HPIS::ThrowOut(elem.second);
            }
        }
        m_ThrowMode = false;

        // test
        m_MainCharacter
            ->MoveByTime(200, m_AniPlayerDestination, m_PlayerMoveDirect);
        m_MainCharacter->Update();
        m_Camera->MoveByTime(200, m_AniCameraDestination);
        m_DungeonMap->PlayerTrigger();
    }

    // player move
    else if (!m_ThrowMode && (Util::Input::IsKeyDown(Util::Keycode::W) || Util::Input::IsKeyDown(Util::Keycode::D) || Util::Input::IsKeyDown(Util::Keycode::S) || Util::Input::IsKeyDown(Util::Keycode::A)) && Music::Tempo::IsTempoInRange(500, musicTime, Music::Player::LoopCounter())) {
        glm::vec2 playerDestination = m_MainCharacter->GetGamePosition();

        if (m_PlayerMoveDirect != Player::NONE) {
            m_PlayerMoveDirect = Player::NONE;
        }
        const std::vector<Util::Keycode> key = {
          Util::Keycode::W,
          Util::Keycode::A,
          Util::Keycode::S,
          Util::Keycode::D};
        const std::vector<glm::vec2> direction =
            {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
        const std::vector<Player::Direction> playerDirection = {
          Player::Direction::UP,
          Player::Direction::LEFT,
          Player::Direction::DOWN,
          Player::Direction::RIGHT};
        const std::vector<glm::vec2> aniPlayerDirection = {
          {0, DUNGEON_TILE_WIDTH * DUNGEON_SCALE},
          {-DUNGEON_TILE_WIDTH * DUNGEON_SCALE, 0},
          {0, -DUNGEON_TILE_WIDTH * DUNGEON_SCALE},
          {DUNGEON_TILE_WIDTH * DUNGEON_SCALE, 0}};
        const std::vector<glm::vec2> aniCameraDirection = {
          {0, -DUNGEON_TILE_WIDTH * DUNGEON_SCALE},
          {DUNGEON_TILE_WIDTH * DUNGEON_SCALE, 0},
          {0, DUNGEON_TILE_WIDTH * DUNGEON_SCALE},
          {-DUNGEON_TILE_WIDTH * DUNGEON_SCALE, 0}};

        for (std::size_t i = 0; i < 4; i++) {
            if (Util::Input::IsKeyDown(key[i])
                && m_DungeonMap->GetMapData()->IsPositionPlayerAct(
                    m_MainCharacter->GetGamePosition() + direction[i]
                )) {
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
                    if (m_DungeonMap->GetMapData()->IsEnemyEmpty(mapIndex)) {
                        m_DungeonMap->GetMapData()->GetEnemy(mapIndex)->Struck(2
                        );

                        Game::Systems::HEIS::DetectHealth(mapIndex);

                        m_Camera->Shake(150, 10);
                    } else if (m_DungeonMap->GetMapData()->IsPositionWall(
                                   playerDestination
                               )) {
                        m_DungeonMap->RemoveWall(
                            m_DungeonMap->GamePostion2MapIndex(playerDestination
                            )
                        );
                    } else if (m_DungeonMap->GetMapData()->IsPositionDoor(
                                   playerDestination
                               )) {
                        m_DungeonMap->OpenDoor(
                            m_DungeonMap->GamePostion2MapIndex(playerDestination
                            )
                        );
                        m_Camera->Shake(100, 10);
                    }
                } else {
                    m_PlayerMoveDirect = playerDirection[i];

                    m_AniPlayerDestination = {
                      m_AniPlayerDestination.x + aniPlayerDirection[i].x,
                      m_AniPlayerDestination.y + aniPlayerDirection[i].y};
                    m_AniCameraDestination = {
                      m_AniCameraDestination.x + aniCameraDirection[i].x,
                      m_AniCameraDestination.y + aniCameraDirection[i].y};
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
    }

    // detect the player
    if (Util::Input::IsKeyDown(Util::Keycode::W)
        || Util::Input::IsKeyDown(Util::Keycode::D)
        || Util::Input::IsKeyDown(Util::Keycode::S)
        || Util::Input::IsKeyDown(Util::Keycode::A)) {
        // m_MusicSystem->clickEvent();
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    Game::System::Update();
    Display::BeatHeart::Update();
    Display::BeatIndicator::Update();
    Music::Tempo::Update(musicTime, 0u, Music::Player::LoopCounter());

    m_MainCharacter->Update();
    m_Camera->Update();
}

std::shared_ptr<Dungeon::Map> App::m_DungeonMap = nullptr;
