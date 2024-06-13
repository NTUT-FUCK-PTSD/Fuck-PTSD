#ifndef APP_HPP
#define APP_HPP

#include <memory>

#include <Core/Context.hpp>
#include <Core/Drawable.hpp>
#include <Util/Keycode.hpp>
#include <Util/Text.hpp>

#include "GameElement.h"
#include "Settings/DeadScreen.h"
#include "Settings/UGameElement.h"
#include "Util/GameObject.hpp"
#include "pch.hpp"  // IWYU pragma: export

#include "Background.hpp"
#include "Camera.h"
#include "Dungeon/Map.h"
#include "Event/EventHandler.h"
#include "Game/Game_config.h"
#include "Player.h"
#include "Settings/Background.hpp"
#include "Settings/Camera.h"
#include "Settings/Window.hpp"

class App {
public:
    App();
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void initializeGame();

    void ClickEvent();

    void Update();

    void End();  // NOLINT(readability-convert-member-functions-to-static)

    static bool                                       m_ThrowMode;
    static std::map<Util::Keycode, Player::Direction> m_MapTableCodeDire;

    static std::shared_ptr<Dungeon::Map> m_DungeonMap;
    static std::shared_ptr<Player>       m_MainCharacter;

    static glm::vec2 m_AniPlayerDestination;
    static glm::vec2 m_AniCameraDestination;

    static Player::Direction m_PlayerMoveDirect;

    static std::shared_ptr<Camera> m_Camera;

private:
    void ValidTask();
    void SetDeadScreen(const bool deadScreenVisible);

private:
    std::shared_ptr<Background> m_Background;
    bool                        m_FirstTime = true;
    bool                        m_IsMainMenu = true;

    State m_CurrentState = State::START;

    glm::vec2 m_CameraPosition = {0, 0};

    Events::EventHandler m_EventHandler;

    std::vector<std::string_view> m_MusicList = {
      Game::Config::MUSIC_ZONE_11,
      Game::Config::MUSIC_ZONE_12,
      Game::Config::MUSIC_ZONE_13,
    };

    std::vector<std::string_view> m_TempoList = {
      Game::Config::TEMPO_ZONE_11,
      Game::Config::TEMPO_ZONE_12,
      Game::Config::TEMPO_ZONE_13,
    };

    std::shared_ptr<Settings::DeadScreen> m_DeadScreen;
    std::shared_ptr<Util::GameObject>     m_InvincibleMode;
    std::shared_ptr<Util::GameObject>     m_OneShotMode;
    bool                                  m_NoBeatMode = false;
    std::shared_ptr<Util::GameObject>     m_NoBeatModeText;
    // addition
};

#endif
