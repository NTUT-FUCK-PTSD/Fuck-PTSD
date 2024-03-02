#include "App.hpp"
#include "Background.hpp"
#include "Character.hpp"
#include "Begin.h"
#include "ToolBoxs.h"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    // init background value
    std::shared_ptr<Background> m_MainMenu = std::make_shared<Background>(ASSETS_DIR"/mainmenu/mainmenu.png");
    std::shared_ptr<Background> m_Continue = std::make_shared<Background>(ASSETS_DIR"/mainmenu/continue.png");

    // create
    Begin::CreateBackground(m_Root, m_MainMenu, m_Continue);

    // save it to App class
    this->SaveBackground = {m_MainMenu, m_Continue};

    // create giraffe
    m_Player1 = std::make_shared<Character>(RESOURCE_DIR"/entities/player1.png");
    m_Player1->SetPosition({-112.5f, -140.5f});
    m_Player1->SetZIndex(50);
    m_Root.AddChild(m_Player1);

    m_Player2 = std::make_shared<Character>(RESOURCE_DIR"/entities/player1.png");
    m_Player2->SetPosition({-112.5f, -140.5f});
    m_Player2->SetZIndex(50);
    m_Player2->SetVisible(false);
    m_Root.AddChild(m_Player2);

    m_CurrentState = State::UPDATE;
}

void App::Update() {

    m_Player1->SetVisible(true);

    // detect any key press, and then remove begin background
    if (ToolBoxs::IsAnyKeyPress()) {
        Begin::RemoveBackground(this->m_Root, this->SaveBackground[0], this->SaveBackground[1]);

        // show protagonist
        m_Player2->SetVisible(true);
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
