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
#include "Event/EventHandler.h"
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

private:
    std::shared_ptr<Background> m_Background;
    bool                        m_FirstTime = true;
    bool                        m_IsMainMenu = true;

    State m_CurrentState = State::START;

    glm::vec2 m_CameraPosition = {0, 0};

    Events::EventHandler m_EventHandler;

    // addition
};

#endif
