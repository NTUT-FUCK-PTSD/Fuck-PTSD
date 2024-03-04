#include "App.hpp"
#include "Background.hpp"
#include "Begin.h"
#include "ToolBoxs.h"

#include "GlobalType.h"

#include "rusty_bridge/lib.h"
#include "tinyxml2.h"

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

    Begin::CreateBackground(
        m_Root, m_Background->m_MainMenu, m_Background->m_Continue);

    // Wait any key click
    while (!ToolBoxs::IsAnyKeyPress()) {
        m_Root.Update();
        context->Update();
    }

    m_Root.RemoveChild(m_Background->m_MainMenu);
    m_Root.RemoveChild(m_Background->m_Continue);

    LOG_INFO(rusty_extern_c_integer());

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    //    m_Player1->SetVisible(true);
    //    m_Player2->SetVisible(true);

    // detect any key press, and then remove begin background
    //    if (ToolBoxs::IsAnyKeyPress()) {
    //    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
