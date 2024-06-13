#include "App.hpp"

#include "Display/BeatIndicator.h"
#include "Event/Event.h"
#include "Music/Tempo.h"
#include "Player_config.h"

App::App() {
    Window::Init();
    m_DeadScreen = std::make_shared<Settings::DeadScreen>();
    m_DeadScreen->SetPosition({0, -200});
    m_DeadScreen->SetVisibleRecursive(false);
    m_Camera->AddUIChild(m_DeadScreen);
    Event::EventQueue.appendListener(
        EventType::ResetMap,
        [this](const Object*, const EventArgs&) {
            m_AniCameraDestination = {0, 0};
            m_AniPlayerDestination = {0, 0};
        }
    );
    m_InvincibleMode = std::make_shared<Util::GameObject>();
    m_InvincibleMode->SetDrawable(std::make_shared<Util::Text>(
        ASSETS_DIR "/font/necrosans-18/necrosans-18.otf",
        18,
        "ACTIVE MODE: INVINCIBLE",
        Players::Config::VAL_COLOR_WHITE
    ));
    m_InvincibleMode->SetZIndex(Players::Config::VAL_ZINDEX);
    m_InvincibleMode->m_Transform.scale = {2, 2};
    m_InvincibleMode->m_Transform.translation = glm::vec2(0, 300);
    m_InvincibleMode->SetVisible(false);
    m_Camera->AddUIChild(m_InvincibleMode);

    m_OneShotMode = std::make_shared<Util::GameObject>();
    m_OneShotMode->SetDrawable(std::make_shared<Util::Text>(
        ASSETS_DIR "/font/necrosans-18/necrosans-18.otf",
        18,
        "ACTIVE MODE: ONESHOT",
        Players::Config::VAL_COLOR_WHITE
    ));
    m_OneShotMode->SetZIndex(Players::Config::VAL_ZINDEX);
    m_OneShotMode->m_Transform.scale = {2, 2};
    m_OneShotMode->m_Transform.translation = glm::vec2(0, 250);
    m_OneShotMode->SetVisible(false);
    m_Camera->AddUIChild(m_OneShotMode);

    m_NoBeatModeText = std::make_shared<Util::GameObject>();
    m_NoBeatModeText->SetDrawable(std::make_shared<Util::Text>(
        ASSETS_DIR "/font/necrosans-18/necrosans-18.otf",
        18,
        "ACTIVE MODE: NO BEAT",
        Players::Config::VAL_COLOR_WHITE
    ));
    m_NoBeatModeText->SetZIndex(Players::Config::VAL_ZINDEX);
    m_NoBeatModeText->m_Transform.scale = {2, 2};
    m_NoBeatModeText->m_Transform.translation = glm::vec2(0, 200);
    m_NoBeatModeText->SetVisible(false);
    m_Camera->AddUIChild(m_NoBeatModeText);

    m_YouWin = std::make_shared<Util::GameObject>();
    m_YouWin->SetDrawable(std::make_shared<Util::Text>(
        ASSETS_DIR "/font/necrosans-18/necrosans-18.otf",
        18,
        "YOU WIN!",
        Players::Config::VAL_COLOR_WHITE
    ));
    m_YouWin->SetZIndex(Players::Config::VAL_ZINDEX);
    m_YouWin->m_Transform.scale = {10, 10};
    m_YouWin->m_Transform.translation = glm::vec2(50, 0);
    m_YouWin->SetVisible(false);
    m_Camera->AddUIChild(m_YouWin);
};

void App::SetDeadScreen(const bool deadScreenVisible) {
    m_MainCharacter->SetVisible(!deadScreenVisible);
    m_DeadScreen->SetVisibleRecursive(deadScreenVisible);
    Music::Tempo::Pause(deadScreenVisible);
    Display::BeatIndicator::Pause(deadScreenVisible);
}
