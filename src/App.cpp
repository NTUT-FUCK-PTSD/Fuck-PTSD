#include "App.hpp"
#include "Background.hpp"
#include "MainCharacter.h"
#include "ToolBoxs.h"

// #include "Coin.h"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

#include "Dungeon/MapHandler.h"

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

    // Wait any key click
    while (!ToolBoxs::IsAnyKeyPress()) {
        m_Camera->Update();
        context->Update();
    }

    // music

    // Configure sound source
    speech.setText("1 2 3   1 2 3   Hello world. Welcome to So-Loud.");

    // initialize SoLoud.
    soloud.init();
    music.load(ASSETS_DIR "/music/add.wav");

    // Play the sound source (we could do this several times if we wanted)
    int voiceHandle = soloud.play(music);

    soloud.setRelativePlaySpeed(voiceHandle, 1.5f);

    // music finish

    // remove background
    m_Camera->RemoveChild(background->GetGameElement());

    // create MainCharacter
    m_MainCharacter = std::make_shared<MainCharacter>(
        ASSETS_DIR "/entities/player1_heads.png",
        ASSETS_DIR "/entities/player1_armor_body.png");
    m_Camera->AddChildren(m_MainCharacter->GetGameElement());

    // Test the Dungeon::Map
    m_DungeonMap = std::make_shared<Dungeon::Map>(
        m_MainCharacter, ASSETS_DIR "/dungeon/MY DUNGEON.xml", 1);
    m_DungeonMap->SetDrawable(
        std::make_shared<Dungeon::MapHandler>(m_DungeonMap));
    m_Camera->AddChild(m_DungeonMap);

    // show the coin
    m_Window->AddChildren(m_Coin->getGameObject());
    m_Window->AddChildren(m_Diamond->getGameObject());

    // add the Tools
    //    m_Window.AddChild(m_Tools->getGameObject());
    m_Window->AddChildren(m_Tools->getGameObjects());

    // display the heart
    m_Window->AddChildren(m_Heart->getGameObjects());

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    // add coin
    if (Util::Input::IsKeyDown(Util::Keycode::B)) {
        m_Coin->plusCoinNumber(10);
        m_Diamond->plusDiamondNumber(10);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::W) ||
        Util::Input::IsKeyDown(Util::Keycode::D) ||
        Util::Input::IsKeyDown(Util::Keycode::S) ||
        Util::Input::IsKeyDown(Util::Keycode::A)) {
        if (m_PlayerMoveDirect != MainCharacter::NONE) {
            m_PlayerMoveDirect = MainCharacter::NONE;
        }
        if (Util::Input::IsKeyDown(Util::Keycode::W)) {
            m_PlayerMoveDirect = MainCharacter::Direction::UP;

            m_AniPlayerDestination = {m_AniPlayerDestination.x,
                                      m_AniPlayerDestination.y +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
            m_AniCameraDestination = {m_AniCameraDestination.x,
                                      m_AniCameraDestination.y -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
            m_PlayerMoveDirect = MainCharacter::Direction::LEFT;
            m_MainCharacter->SetFaceTo(MainCharacter::Direction::LEFT);

            m_AniPlayerDestination = {m_AniPlayerDestination.x -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniPlayerDestination.y};
            m_AniCameraDestination = {m_AniCameraDestination.x +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniCameraDestination.y};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
            m_PlayerMoveDirect = MainCharacter::Direction::DOWN;

            m_AniPlayerDestination = {m_AniPlayerDestination.x,
                                      m_AniPlayerDestination.y -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
            m_AniCameraDestination = {m_AniCameraDestination.x,
                                      m_AniCameraDestination.y +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
            m_PlayerMoveDirect = MainCharacter::Direction::RIGHT;
            m_MainCharacter->SetFaceTo(MainCharacter::Direction::RIGHT);

            m_AniPlayerDestination = {m_AniPlayerDestination.x +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniPlayerDestination.y};
            m_AniCameraDestination = {m_AniCameraDestination.x -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniCameraDestination.y};
        }
        m_MainCharacter->MoveByTime(200, m_AniPlayerDestination,
                                    m_PlayerMoveDirect);
        m_Camera->MoveByTime(200, m_AniCameraDestination);
        m_DungeonMap->TempoUpdate();
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    //    LOG_INFO(rusty_extern_c_integer());

    m_MainCharacter->Update();
    m_Window->Update();
    m_Camera->Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
