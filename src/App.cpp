#include "App.hpp"
#include "Animation.h"
#include "Background.hpp"
#include "Event.h"
#include "EventHandler.h"
#include "MainCharacter.h"
#include "PollHandler.h"
#include "ToolBoxs.h"
#include "rusty_bridge/lib.h"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

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
    Dungeon::Map Test(ASSETS_DIR "/level/test.xml", 1);

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

    current_frame = ToolBoxs::FrameCounter(current_frame);

    //    PollHandler poll;
    //    poll.add(Event::isKeyDown_W, EventHandler::KeyDown_W);
    //
    //    poll.listen();

    //    auto isFinish = Animation::move_player(current_frame,
    //    animationStartFrame,
    //                                           m_PlayerMoveDirect,
    //                                           m_MainCharacter);
    //
    //    if (isFinish) {
    //        m_PlayerMoveDirect = MainCharacter::NONE;
    //    }
    //
    //    glm::vec2 currnet = {-m_CameraPosition.x, -m_CameraPosition.y};
    //    if (Util::Input::IsKeyDown(Util::Keycode::W)) {
    //        m_PlayerMoveDirect = MainCharacter::Direction::UP;
    //        animationStartFrame = current_frame + 1;
    //        currnet.y -= 10;
    //        m_MainCharacter->SetPosition(currnet);
    //
    //        m_CameraPosition.y += 10;
    //    }
    //    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
    //        m_PlayerMoveDirect = MainCharacter::Direction::LEFT;
    //        animationStartFrame = current_frame + 1;
    //        currnet.x += 10;
    //        m_MainCharacter->SetPosition(currnet);
    //
    //        m_CameraPosition.x -= 10;
    //    }
    //    if (Util::Input::IsKeyDown(Util::Keycode::S)) {
    //        m_PlayerMoveDirect = MainCharacter::Direction::DOWN;
    //        animationStartFrame = current_frame + 1;
    //        currnet.y += 10;
    //        m_MainCharacter->SetPosition(currnet);
    //        m_CameraPosition.y -= 10;
    //    }
    //    if (Util::Input::IsKeyDown(Util::Keycode::D)) {
    //        m_PlayerMoveDirect = MainCharacter::Direction::RIGHT;
    //        animationStartFrame = current_frame + 1;
    //        currnet.x -= 10;
    //        m_MainCharacter->SetPosition(currnet);
    //
    //        m_CameraPosition.x += 10;
    //    }

    m_Camera.SetPosition(m_CameraPosition);

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    //    LOG_INFO(rusty_extern_c_integer());

    m_Camera.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
