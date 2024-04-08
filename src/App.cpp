#include "App.hpp"
#include "Background.hpp"
#include "Dungeon/MapHandler.h"
#include "Player.h"
#include "ToolBoxs.h"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"
#include <thread>

using namespace tinyxml2;

extern "C" {
int32_t rusty_extern_c_integer();
}

// show the start background and listen the keypress
void App::Start(std::shared_ptr<Core::Context>
                    context) { // the value context is come from main.cpp
    LOG_TRACE("Start");

    // create background
    const auto background = std::make_shared<Background>();
    m_Camera->AddChild(background->GetGameElement());

    // play main background music
    m_MusicSystem->playMusic(ASSETS_DIR "/music/intro_onlyMusic.ogg", true);
    //    m_MusicSystem->skipToTargetTime(118.2f);

    // Wait any key click
    while (!ToolBoxs::IsAnyKeyPress()) {
        if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
            Util::Input::IfExit()) {
            m_CurrentState = State::END;
        }
        m_MusicSystem->Update();
        m_Camera->Update();
        context->Update();
    }

    // play lobby music
    //    m_MusicSystem->playMusic(ASSETS_DIR"/music/lobby.ogg", true);
    //    m_MusicSystem->readTempoFile(ASSETS_DIR"/music/lobby.txt");
    //    m_MusicSystem->setSpeed(1.2);

    // play zone1 leve1
    m_MusicSystem->playMusic(ASSETS_DIR "/music/zone1_1.ogg", true);
    m_MusicSystem->readTempoFile(ASSETS_DIR "/music/zone1_1.txt");

    // remove background
    m_Camera->RemoveChild(background->GetGameElement());

    // create Player
    m_MainCharacter = std::make_shared<Player>();
    m_MainCharacter->SetHeadImage(ASSETS_DIR "/entities/player1_heads.png");
    m_MainCharacter->SetBodyImage(ASSETS_DIR
                                  "/entities/player1_armor_body.png");
    m_Camera->AddChild(m_MainCharacter->GetGameElement());
    m_Window->AddChild(m_MainCharacter->GetWindowElement());

    // Test the Dungeon::Map
    m_DungeonMap = std::make_shared<Dungeon::Map>(
        m_MainCharacter, ASSETS_DIR "/dungeon/MY DUNGEON.xml", 1);
    m_DungeonMap->SetDrawable(
        std::make_shared<Dungeon::MapHandler>(m_DungeonMap));
    m_Camera->AddChild(m_DungeonMap);

    // display the tempo heart in music System
    m_Window->AddChild(m_MusicSystem->getGameObject());

    m_CurrentState = State::UPDATE;
}

void App::Update() {

    // add coin
    //    if (Util::Input::IsKeyDown(Util::Keycode::B)) {
    //        m_Coin->plusCoinNumber(10);
    //        m_Diamond->plusDiamondNumber(10);
    //    }

    // detect the player
    if (Util::Input::IsKeyDown(Util::Keycode::W) ||
        Util::Input::IsKeyDown(Util::Keycode::D) ||
        Util::Input::IsKeyDown(Util::Keycode::S) ||
        Util::Input::IsKeyDown(Util::Keycode::A)) {
        m_MusicSystem->clickEvent();
    }

    // player move
    if ((Util::Input::IsKeyDown(Util::Keycode::W) ||
         Util::Input::IsKeyDown(Util::Keycode::D) ||
         Util::Input::IsKeyDown(Util::Keycode::S) ||
         Util::Input::IsKeyDown(Util::Keycode::A)) &&
        m_MusicSystem->TempoTrigger()) {

        if (m_PlayerMoveDirect != Player::NONE) {
            m_PlayerMoveDirect = Player::NONE;
        }
        if (Util::Input::IsKeyDown(Util::Keycode::W) &&
            m_DungeonMap->GetMapData()->IsPositionWalkable(
                m_MainCharacter->GetGamePosition() + glm::vec2(0, -1))) {
            m_PlayerMoveDirect = Player::Direction::UP;

            m_AniPlayerDestination = {m_AniPlayerDestination.x,
                                      m_AniPlayerDestination.y +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
            m_AniCameraDestination = {m_AniCameraDestination.x,
                                      m_AniCameraDestination.y -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::A) &&
                 m_DungeonMap->GetMapData()->IsPositionWalkable(
                     m_MainCharacter->GetGamePosition() + glm::vec2(-1, 0))) {
            m_PlayerMoveDirect = Player::Direction::LEFT;
            m_MainCharacter->SetFaceTo(Player::Direction::LEFT);

            m_AniPlayerDestination = {m_AniPlayerDestination.x -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniPlayerDestination.y};
            m_AniCameraDestination = {m_AniCameraDestination.x +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniCameraDestination.y};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::S) &&
                 m_DungeonMap->GetMapData()->IsPositionWalkable(
                     m_MainCharacter->GetGamePosition() + glm::vec2(0, 1))) {
            m_PlayerMoveDirect = Player::Direction::DOWN;

            m_AniPlayerDestination = {m_AniPlayerDestination.x,
                                      m_AniPlayerDestination.y -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
            m_AniCameraDestination = {m_AniCameraDestination.x,
                                      m_AniCameraDestination.y +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::D) &&
                 m_DungeonMap->GetMapData()->IsPositionWalkable(
                     m_MainCharacter->GetGamePosition() + glm::vec2(1, 0))) {
            m_PlayerMoveDirect = Player::Direction::RIGHT;
            m_MainCharacter->SetFaceTo(Player::Direction::RIGHT);

            m_AniPlayerDestination = {m_AniPlayerDestination.x +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniPlayerDestination.y};
            m_AniCameraDestination = {m_AniCameraDestination.x -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniCameraDestination.y};
        }
        m_MainCharacter->MoveByTime(200, m_AniPlayerDestination,
                                    m_PlayerMoveDirect);
        m_MainCharacter->Update();
        m_Camera->MoveByTime(200, m_AniCameraDestination);
        m_DungeonMap->TempoUpdate();
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    //    LOG_INFO(rusty_extern_c_integer());

    m_MusicSystem->Update();
    m_MainCharacter->Update();
    m_Window->Update();
    m_Camera->Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
