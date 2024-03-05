//
// Created by adven on 2024/3/2.
//

#include "Begin.h"

#include "App.hpp"
#include "Background.hpp"
#include "Character/Character.hpp"

#include "Util/Renderer.hpp"

void Begin::CreateBackground(Util::Renderer& m_Root, std::shared_ptr<Background> m_MainMenu, std::shared_ptr<Background> m_Continue) {
//    m_MainMenu = std::make_shared<Background>(ASSETS_DIR"/mainmenu/mainmenu.png");
    m_MainMenu->SetZIndex(3);

//    m_Continue = std::make_shared<Background>(ASSETS_DIR"/mainmenu/continue.png");
    m_Continue->SetPosition({-0.5f, -365.5f});
    m_Continue->SetZIndex(5);

    m_Root.AddChild(m_MainMenu);
    m_Root.AddChild(m_Continue);
}

void Begin::RemoveBackground(Util::Renderer& m_Root, std::shared_ptr<Background> m_MainMenu, std::shared_ptr<Background> m_Continue) {
    m_Root.RemoveChild(m_MainMenu);
    m_Root.RemoveChild(m_Continue);
}