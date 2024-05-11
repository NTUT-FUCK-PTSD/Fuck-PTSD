//
// Created by adven on 2024/5/10.
//

#include "App.hpp"

#include "Util/Logger.hpp"

#include <Util/Input.hpp>
#include "Music/Player.h"

void App::Start() {
    LOG_TRACE("Start");
    if (m_FirstTime) {
        m_FirstTime = false;
        // create background
        m_Background = std::make_shared<Background>();
        m_Camera->AddChild(m_Background->GetGameElement());

        // play main background music
        Music::Player::Init();
        Music::Player::PlayMusic(
            ASSETS_DIR "/music/intro_onlyMusic.ogg",
            true,
            0.5f,
            1.0f
        );

        //    m_MusicSystem->skipToTargetTime(118.2f);
    }

    // Wait any key click
    if (ToolBoxs::IsAnyKeyPress()) {
        m_IsMainMenu = false;
    }

    // m_MusicSystem->Update();
    m_Camera->Update();

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (m_IsMainMenu) {
        return;
    }

    initializeGame();
    ClickEvent();

    m_CurrentState = State::UPDATE;
}

std::map<Util::Keycode, Player::Direction> App::m_MapTableCodeDire = {
  {Util::Keycode::W, Player::Direction::UP},
  {Util::Keycode::D, Player::Direction::RIGHT},
  {Util::Keycode::S, Player::Direction::DOWN},
  {Util::Keycode::A, Player::Direction::LEFT}
};

std::shared_ptr<Player> App::m_MainCharacter = nullptr;
bool                    App::m_ThrowMode = false;

glm::vec2 App::m_AniPlayerDestination = {0, 0};
glm::vec2 App::m_AniCameraDestination = {0, 0};

Player::Direction       App::m_PlayerMoveDirect = Player::Direction::NONE;
std::shared_ptr<Camera> App::m_Camera = std::make_shared<Camera>();
