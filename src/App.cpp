#include "Animation.h"
#include "App.hpp"
#include "Background.hpp"
#include "MainCharacter.h"
#include "ToolBoxs.h"
#include "rusty_bridge/lib.h"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

#include "Dungeon/Map.h"

using namespace tinyxml2;

extern "C" {
int32_t rusty_extern_c_integer();
}

// show the start background and listen the keypress
void App::Start(std::shared_ptr<Core::Context>
                    context) { // the value context is come from main.cpp
    LOG_TRACE("Start");
    // Test the Dungeon::Map
    Dungeon::Map Test(ASSETS_DIR "/dungeon/test.xml", 1);

    // create background
    const auto background = std::make_shared<Background>();
    m_Camera.AddChild(background->GetGameElement());

    // Wait any key click
    while (!ToolBoxs::IsAnyKeyPress()) {
        m_Camera.Update();
        context->Update();
    }

    // create MainCharacter
    m_MainCharacter = std::make_shared<MainCharacter>();
    m_Camera.AddChildren(m_MainCharacter->GetGameElement());

    // remove background
    m_Camera.RemoveChild(background->GetGameElement());
    m_Camera.AddChildren(Test.GetChildren());

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    m_CameraPosition = Animation::moveCameraByTime(
        m_AnimationStartTime, 200, m_AniCameraDestination, m_CameraPosition);

    Animation::movePlayerAnimation(m_AnimationStartTime, 200, m_AniPlayerMotion,
                                   m_MainCharacter);
    auto isFinish = Animation::movePlayerByTime(
        m_AnimationStartTime, 200, m_AniPlayerDestination, m_MainCharacter);

    if (isFinish) {
        m_PlayerMoveDirect = MainCharacter::NONE;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::W) ||
        Util::Input::IsKeyDown(Util::Keycode::D) ||
        Util::Input::IsKeyDown(Util::Keycode::S) ||
        Util::Input::IsKeyDown(Util::Keycode::A)) {
        if (m_PlayerMoveDirect != MainCharacter::NONE) {
            m_PlayerMoveDirect = MainCharacter::NONE;
            m_MainCharacter->SetPosition(m_AniPlayerDestination);
            m_CameraPosition = m_AniCameraDestination;
        }
        glm::vec2 current = {-m_CameraPosition.x, -m_CameraPosition.y};
        if (Util::Input::IsKeyDown(Util::Keycode::W)) {
            m_PlayerMoveDirect = MainCharacter::Direction::UP;

            m_AnimationStartTime = Util::Time::GetElapsedTimeMs();
            m_AniPlayerStartPosition = m_MainCharacter->GetPosition();
            m_AniPlayerDestination = {m_AniPlayerDestination.x,
                                      m_AniPlayerDestination.y +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
            m_AniPlayerMotion = {0, Dungeon::DUNGEON_TILE_WIDTH};
            m_AniCameraDestination = {m_AniCameraDestination.x,
                                      m_AniCameraDestination.y -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
            m_PlayerMoveDirect = MainCharacter::Direction::LEFT;
            m_MainCharacter->SetFaceTo(MainCharacter::Direction::LEFT);

            m_AnimationStartTime = Util::Time::GetElapsedTimeMs();
            m_AniPlayerStartPosition = m_MainCharacter->GetPosition();
            m_AniPlayerDestination = {m_AniPlayerDestination.x -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniPlayerDestination.y};
            m_AniPlayerMotion = {Dungeon::DUNGEON_TILE_WIDTH / 2,
                                 Dungeon::DUNGEON_TILE_WIDTH};
            m_AniCameraDestination = {m_AniCameraDestination.x +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniCameraDestination.y};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
            m_PlayerMoveDirect = MainCharacter::Direction::DOWN;

            m_AnimationStartTime = Util::Time::GetElapsedTimeMs();
            m_AniPlayerStartPosition = m_MainCharacter->GetPosition();
            m_AniPlayerDestination = {m_AniPlayerDestination.x,
                                      m_AniPlayerDestination.y -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
            m_AniPlayerMotion = {-Dungeon::DUNGEON_TILE_WIDTH / 4,
                                 Dungeon::DUNGEON_TILE_WIDTH};
            m_AniCameraDestination = {m_AniCameraDestination.x,
                                      m_AniCameraDestination.y +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3};
        }
        else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
            m_PlayerMoveDirect = MainCharacter::Direction::RIGHT;
            m_MainCharacter->SetFaceTo(MainCharacter::Direction::RIGHT);

            m_AnimationStartTime = Util::Time::GetElapsedTimeMs();
            m_AniPlayerStartPosition = m_MainCharacter->GetPosition();
            m_AniPlayerDestination = {m_AniPlayerDestination.x +
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniPlayerDestination.y};
            m_AniPlayerMotion = {-Dungeon::DUNGEON_TILE_WIDTH / 2,
                                 Dungeon::DUNGEON_TILE_WIDTH};
            m_AniCameraDestination = {m_AniCameraDestination.x -
                                          Dungeon::DUNGEON_TILE_WIDTH * 3,
                                      m_AniCameraDestination.y};
        }
    }

    m_Camera.SetPosition(m_CameraPosition);

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    //    LOG_INFO(rusty_extern_c_integer());

    m_MainCharacter->Update();
    m_Camera.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
