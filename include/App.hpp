#ifndef APP_HPP
#define APP_HPP
#include "Background.hpp"
#include "Camera.h"
#include "Character/Character.hpp"
#include "Core/Context.hpp"
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
    std::size_t animationStartFrame = 0;

    State m_CurrentState = State::START;

    MainCharacter::Direction m_PlayerMoveDirect =
        MainCharacter::Direction::NONE;

    std::shared_ptr<MainCharacter> m_MainCharacter;

    int current_frame = 0;

    Camera m_Camera;
    glm::vec2 m_CameraPosition = {0, 0};
};

#endif
