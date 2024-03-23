//
// Created by adven on 2024/3/22.
//
#include "Coin.h"
#include "Util/Color.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

//
Coin::Coin() {
    m_text = std::make_shared<Util::Text>(
        m_TextStylePath, m_fontSize, m_showText, Util::Color(255, 255, 255));
    const auto CoinImage = std::make_shared<Util::Image>(m_imagePath);

    m_CoinText->SetDrawable(m_text);
    m_CoinImage->SetDrawable(CoinImage);

    m_CoinText->SetZIndex((float)m_ZIndex);
    m_CoinImage->SetZIndex((float)m_ZIndex);

    m_CoinText->SetScale(m_FontScale);
    m_CoinImage->SetScale(m_ImageScale);

    //    m_CoinText->SetPosition({m_Position.x + 100, m_Position.y});

    m_CoinImage->SetPosition(m_Position);

    toLeftSideCoinText();
}

std::vector<std::shared_ptr<Util::GameObject>> Coin::getGameObject() {
    return {m_CoinText, m_CoinImage};
}

void Coin::toLeftSideCoinText() {

    // left point
    glm::vec2 initPos = {m_Position.x + 50, m_Position.y};
    const glm::vec2 modifyPos = {initPos.x + m_text->GetSize().x * 2.5,
                                 initPos.y};
    m_CoinText->SetPosition(modifyPos);
    //    LOG_DEBUG((glm::vec2){a.x + m_text->GetSize().x,
    //    m_text->GetSize().y});
}

void Coin::plusCoinNumber(const int number) {
    m_Number += number;
    const std::string str = '*' + std::to_string(m_Number);
    m_text->SetText(str);

    toLeftSideCoinText();
}
