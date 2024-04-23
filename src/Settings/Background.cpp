//
// Created by adven on 2024/3/1.
//
#include "Background.hpp"

#include "Util/Image.hpp"

#include "Settings/Window.hpp"

Background::Background() {
    const auto ContinueImage = std::make_shared<Util::Image>(m_ContinueImagePath
    );
    const auto MainMenuImage = std::make_shared<Util::Image>(m_MainMenuImagePath
    );

    m_MainMenu->SetDrawable(MainMenuImage);
    m_MainMenu->SetZIndex(99);
    m_MainMenu->SetScale(glm::vec2(DUNGEON_SCALE, DUNGEON_SCALE));

    m_Continue->SetDrawable(ContinueImage);
    m_Continue->SetPosition({-0.5f, -365.4f});
    m_Continue->SetZIndex(100);
    m_Continue->SetScale(glm::vec2(DUNGEON_SCALE, DUNGEON_SCALE));

    m_Background->AddChild(m_MainMenu);
    m_Background->AddChild(m_Continue);

    m_Background->SetVisible(false);
}

std::shared_ptr<GameElement> Background::GetGameElement() {
    return m_Background;
}
