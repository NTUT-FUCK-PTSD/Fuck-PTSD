#include "App.hpp"
#include "Background.hpp"
#include "Begin.h"
#include "GlobalType.h"
#include "MainCharacter.h"
#include "ToolBoxs.h"

#include "rusty_bridge/lib.h"
#include "tinyxml2.h"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

using namespace tinyxml2;

extern "C" {
int32_t rusty_extern_c_integer();
}

// show the start background and listen the keypress
void App::Start(std::shared_ptr<Core::Context>
                    context) { // the value context is come from main.cpp
    LOG_TRACE("Start");

    auto m_Background = std::make_shared<GlobalType::TBackground>();

    // init background value
    m_Background->m_Continue =
        std::make_shared<Background>(ASSETS_DIR "/mainmenu/continue.png");
    m_Background->m_MainMenu =
        std::make_shared<Background>(ASSETS_DIR "/mainmenu/mainmenu.png");

    Begin::CreateBackground(m_Camera.GetRenderer(), m_Background->m_MainMenu,
                            m_Background->m_Continue);

    // Wait any key click
    while (!ToolBoxs::IsAnyKeyPress()) {
        m_Camera.Update();
        context->Update();
    }

    // create MainCharacter
    m_MainCharacter = std::make_shared<MainCharacter>();

    //    m_Camera.AddChild(m_MainCharacter->Render());
    m_Camera.AddChildren(m_MainCharacter->Render());

    // remove background
    m_Camera.RemoveChild(m_Background->m_MainMenu);
    m_Camera.RemoveChild(m_Background->m_Continue);

    m_CurrentState = State::UPDATE;
}

void App::Update() {

    //    LOG_DEBUG(current_frame);
    current_frame = ToolBoxs::FrameCounter(current_frame);

    status = m_MainCharacter->player_move_animation(current_frame,
                                                    m_PlayerMoveDirect, status);

    if ((m_MainCharacter->GetStartMoveFrame() + 15 == current_frame) ||
        (m_MainCharacter->GetStartMoveFrame() + 15 - 60 == current_frame)) {
        LOG_DEBUG(m_MainCharacter->GetPosition());
        status = false;
        m_PlayerMoveDirect = MainCharacter::Direction::NONE;
    }

    //    LOG_DEBUG(m_MainCharacter->GetStartMoveFrame());
    //    LOG_DEBUG(status);

    //    LOG_ERROR(Fuck_Fuck());
    //    auto m_MainCharacter = new MainCharacter();

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */

    if (Util::Input::IsKeyDown(Util::Keycode::W)) {
        m_CameraPosition.y += 10;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        m_CameraPosition.x -= 10;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        m_CameraPosition.y -= 10;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        m_PlayerMoveDirect = MainCharacter::Direction::RIGHT;

        //        m_CameraPosition.x += 10;
    }
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
