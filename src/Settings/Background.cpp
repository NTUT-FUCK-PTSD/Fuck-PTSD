//
// Created by adven on 2024/3/1.
//
#include "Background.hpp"

#include "Util/Image.hpp"

Background::Background() {
    const auto ContinueImage =
        std::make_shared<Util::Image>(m_ContinueImagePath);
    const auto MainMenuImage =
        std::make_shared<Util::Image>(m_MainMenuImagePath);

    m_MainMenu->SetDrawable(MainMenuImage);
    m_MainMenu->SetZIndex(3);
    m_MainMenu->SetScale({3, 3});

    m_Continue->SetDrawable(ContinueImage);
    m_Continue->SetPosition({-0.5f, -365.4f});
    m_Continue->SetZIndex(5);
    m_Continue->SetScale({3, 3});

    m_Background->AddChild(m_MainMenu);
    m_Background->AddChild(m_Continue);

    m_Background->SetVisible(false);
}

std::shared_ptr<GameElement> Background::GetGameElement() {
    return m_Background;
}
