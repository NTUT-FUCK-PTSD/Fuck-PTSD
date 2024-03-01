#include "App.hpp"
#include "Background.hpp"
#include "Character.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    //init


    // create background
    m_Player1 = std::make_shared<Character>(RESOURCE_DIR"/entities/player1.png");
    m_Player1->SetPosition({-112.5f, -140.5f});
    m_Player1->SetZIndex(50);
    m_Root.AddChild(m_Player1);

    m_StartBackground = std::make_shared<Background>(ASSETS_DIR"/mainmenu/mainmenu.png");
    m_StartBackground->SetZIndex(3);

    m_Continue = std::make_shared<Background>(ASSETS_DIR"/mainmenu/continue.png");
    m_Continue->SetPosition({-0.5f, -365.5f});
    m_Continue->SetZIndex(5);

    m_Root.AddChild(m_StartBackground);
    m_Root.AddChild(m_Continue);
    m_CurrentState = State::UPDATE;
}

void App::Update() {

    m_Player1->SetVisible(true);



    // detect any key press
    for (int i = 0; i < 512; i++) {
        if (Util::Input::IsKeyPressed((Util::Keycode)i)) {
            m_Root.RemoveChild(m_Continue);
            m_Root.RemoveChild(m_StartBackground);
        }
    }
    
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
