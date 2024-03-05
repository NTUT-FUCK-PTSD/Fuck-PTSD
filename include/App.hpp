#ifndef APP_HPP
#define APP_HPP
#include "Background.hpp"
#include "Character/Character.hpp"
#include "Core/Context.hpp"
#include "MainCharacter.h"
#include "SpriteSheet.hpp"
#include "Util/Root.hpp"
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

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;

    Util::Root m_Root;
};

#endif
