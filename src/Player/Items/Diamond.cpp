//
// Created by adven on 2024/3/22.
//
#include "Player/Items/Diamond.h"
#include "Player/Items/Coin.h"
#include "Util/Color.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

//
Diamond::Diamond() {
    m_text = std::make_shared<Util::Text>(
        m_TextStylePath, m_fontSize, m_showText, Util::Color(255, 255, 255));
    const auto CoinImage = std::make_shared<Util::Image>(m_imagePath);

    m_DiamondText->SetDrawable(m_text);
    m_DiamondImage->SetDrawable(CoinImage);

    m_DiamondText->SetZIndex((float)m_ZIndex);
    m_DiamondImage->SetZIndex((float)m_ZIndex);

    m_DiamondText->SetScale(m_FontScale);
    m_DiamondImage->SetScale(m_ImageScale);

    //    m_CoinText->SetPosition({m_Position.x + 100, m_Position.y});

    m_DiamondImage->SetPosition(m_Position);

    toLeftSideDiamondText();
}

std::vector<std::shared_ptr<Util::GameObject>> Diamond::getGameObject() {
    return {m_DiamondText, m_DiamondImage};
}

void Diamond::toLeftSideDiamondText() {

    // left point
    glm::vec2 initPos = {m_Position.x + 50, m_Position.y};
    const glm::vec2 modifyPos = {initPos.x + m_text->GetSize().x * 2.5,
                                 initPos.y};
    m_DiamondText->SetPosition(modifyPos);
}

void Diamond::plusDiamondNumber(const int number) {
    m_Number += number;
    const std::string str = '*' + std::to_string(m_Number);
    m_text->SetText(str);

    toLeftSideDiamondText();
}

std::shared_ptr<GameElement> Diamond::GetGameObject() {
    m_Diamond -> AddChild(m_DiamondImage);
    m_Diamond->AddChild(m_DiamondText);
    m_Diamond->SetVisible(false);

    return m_Diamond;
}
