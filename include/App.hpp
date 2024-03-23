#ifndef APP_HPP
#define APP_HPP
#include "Background.hpp"
#include "Animation.h"
#include "Background.hpp"
#include "MainCharacter.h"
#include "ToolBoxs.h"
#include "Camera.h"
#include "Character/Character.hpp"
#include "Coin.h"
#include "Core/Context.hpp"
#include "Core/Drawable.hpp"
#include "Diamond.h"
#include "Dungeon/Map.h"
#include "Heart.h"
#include "MainCharacter.h"
#include "SpriteSheet.hpp"
#include "Util/Text.hpp"

#include "pch_extreme.h"
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
    //    std::shared_ptr<Heart> heart = std::make_shared<Heart>();
    std::shared_ptr<Coin> m_Coin = std::make_shared<Coin>();
    std::shared_ptr<Diamond> m_Diamond = std::make_shared<Diamond>();

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
    std::shared_ptr<Camera> m_Window = std::make_shared<Camera>();
    ;
    glm::vec2 m_CameraPosition = {0, 0};

    std::shared_ptr<Dungeon::Map> m_DungeonMap;
};

#endif
