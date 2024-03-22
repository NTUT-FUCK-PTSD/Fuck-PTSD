//
// Created by adven on 2024/3/22.
//
#include "Coin.h"
#include "Util/Color.hpp"
#include "Util/Image.hpp"

//
Coin::Coin() {
    m_text = std::make_shared<Util::Text>(m_TextStylePath, m_fontSize, "x1",
                                          Util::Color(255, 255, 255));
    const auto CoinImage = std::make_shared<Util::Image>(m_imagePath);

    m_CoinText->SetDrawable(m_text);
    m_CoinImage->SetDrawable(CoinImage);

    m_CoinText->SetZIndex((float)m_ZIndex);
    m_CoinImage->SetZIndex((float)m_ZIndex);

    m_CoinText->SetScale(m_Scale);
    m_CoinImage->SetScale(m_Scale);

    m_CoinText->SetPosition({m_Position.x + 30, m_Position.y});
    m_CoinImage->SetPosition(m_Position);
}
std::vector<std::shared_ptr<Util::GameObject>> Coin::getGameObject() {
    return {m_CoinText, m_CoinImage};
}
