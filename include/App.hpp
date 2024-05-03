#ifndef APP_HPP
#define APP_HPP

#include <memory>

#include <Core/Context.hpp>
#include <Core/Drawable.hpp>
#include <Util/Keycode.hpp>
#include <Util/Text.hpp>

#include "Background.hpp"
#include "Camera.h"
#include "Dungeon/Map.h"
#include "Player.h"
#include "Settings/Background.hpp"
#include "Settings/Camera.h"
#include "pch.hpp"  // IWYU pragma: export

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End();  // NOLINT(readability-convert-member-functions-to-static)

    std::string Print(std::string s) { return s; }

private:
    void ValidTask();

private:
    // mainmenu
    std::shared_ptr<Background> m_Background;
    bool                        m_FirstTime = true;
    bool                        m_IsMainMenu = true;
    bool                        m_ThrowMode = false;

    // settings
    glm::vec2 m_AniPlayerDestination = {0.0f, 0.0f};
    glm::vec2 m_AniCameraDestination = {0.0f, 0.0f};

    State m_CurrentState = State::START;

    Player::Direction m_PlayerMoveDirect = Player::Direction::NONE;

    std::shared_ptr<Player> m_MainCharacter;

    std::shared_ptr<Camera> m_Camera = std::make_shared<Camera>();

    glm::vec2 m_CameraPosition = {0, 0};

    std::shared_ptr<Dungeon::Map> m_DungeonMap;
    std::size_t                   m_BeforeTempoIndex = 0;
    std::size_t                   m_TempoIndex = 0;

    // addition
    static std::map<Util::Keycode, Player::Direction> m_MapTableCodeDire;
};

#endif
