#ifndef APP_HPP
#define APP_HPP
#include "Background.hpp"
#include "Camera.h"
#include "Character/Character.hpp"
#include "Core/Context.hpp"
#include "Dungeon/Map.h"
#include "MainCharacter.h"
#include "SpriteSheet.hpp"
#include "pch.hpp" // IWYU pragma: export

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start(std::shared_ptr<Core::Context> context);

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    std::string Print(std::string s) { return s; }

private:
    void ValidTask();

private:
    unsigned long m_AnimationStartTime = 0;
    glm::vec2 m_AniPlayerStartPosition = {0.0f, 0.0f};
    glm::vec2 m_AniPlayerMotion = {0.0f, 0.0f};
    glm::vec2 m_AniPlayerDestination = {0.0f, 0.0f};
    glm::vec2 m_AniCameraDestination = {0.0f, 0.0f};

    State m_CurrentState = State::START;

    MainCharacter::Direction m_PlayerMoveDirect =
        MainCharacter::Direction::NONE;

    std::shared_ptr<MainCharacter> m_MainCharacter;

    std::shared_ptr<Camera> m_Camera = std::make_shared<Camera>();
    glm::vec2 m_CameraPosition = {0, 0};

    std::shared_ptr<Dungeon::Map> m_DungeonMap;
};

#endif
