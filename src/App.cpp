#include "App.hpp"
#include "Background.hpp"
#include "Begin.h"
#include "Character/Character.hpp"
#include "ToolBoxs.h"

#include "rusty_bridge/lib.h"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

extern "C" {
int32_t rusty_extern_c_integer();
}

void App::Start() {
    LOG_TRACE("Start");

    // init background value
    std::shared_ptr<Background> m_MainMenu =
        std::make_shared<Background>(ASSETS_DIR "/mainmenu/mainmenu.png");
    std::shared_ptr<Background> m_Continue =
        std::make_shared<Background>(ASSETS_DIR "/mainmenu/continue.png");

    // create
    Begin::CreateBackground(m_Root, m_MainMenu, m_Continue);

    // save it to App class
    this->m_SaveBackground = {m_MainMenu, m_Continue};

    m_Protagonist = std::make_shared<Character>(ASSETS_DIR"/entities/player1_armor_body.png");
    m_Protagonist->SetAnimation(glm::vec2(24.0f, 24.0f),std::vector<std::size_t>{0, 1, 2, 3}, true, 100, true, 100);
    m_Protagonist->SetPosition({-200.0f, -250.0f});
    m_Protagonist->SetZIndex(50);
    m_Root.AddChild(m_Protagonist);

    m_Protagonist = std::make_shared<Character>(ASSETS_DIR"/entities/player1_heads.png");
    m_Protagonist->SetAnimation(glm::vec2(24.0f, 13.0f),std::vector<std::size_t>{0, 1, 2, 3}, true, 100, true, 100);
    m_Protagonist->SetPosition({-200.0f, -250.0f});
    m_Protagonist->SetZIndex(50);
    m_Root.AddChild(m_Protagonist);



    // change state to update
    m_CurrentState = State::UPDATE;
}

void App::Update() {
//    m_Player1->SetVisible(true);
//    m_Player2->SetVisible(true);

    // detect any key press, and then remove begin background
    if (ToolBoxs::IsAnyKeyPress()) {
        Begin::RemoveBackground(this->m_Root, this->m_SaveBackground[0],
                                this->m_SaveBackground[1]);

        LOG_INFO(rusty_extern_c_integer());
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
