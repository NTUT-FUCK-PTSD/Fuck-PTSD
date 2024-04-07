#ifndef FUCK_PTSD_COIN_H
#define FUCK_PTSD_COIN_H

#include "Animation.h"
#include "GameElement.h"
#include "Util/Text.hpp"
#include <iostream>
#include <memory>

class Coin final : public Animation {
public:
    Coin();

    virtual ~Coin() = default;

    void plusCoinNumber(const int number);

    void SetPosition(const glm::vec2 &position);

    std::size_t GetCoin();

    // return GameObject
    std::vector<std::shared_ptr<Util::GameObject>> getGameObject();

    std::shared_ptr<GameElement> GetGameObject();

    void Update();

private:
    void toLeftSideCoinText();

    std::size_t m_Number = 0;
    std::size_t m_ZIndex = 50;
    std::size_t m_fontSize = 6;
    glm::vec2 m_ImageScale = {3, 3};
    glm::vec2 m_FontScale = {5, 5};
    std::string m_showText = "*0";
    std::string m_imagePath = ASSETS_DIR "/gui/hud_coins.png";

    std::string m_TextStylePath =
        ASSETS_DIR "/font/necrosans-6/necrosans-6.otf";

    glm::vec2 m_Position = {585, 350};
    glm::vec2 m_GamePosition = {0, 0};

    std::shared_ptr<Util::Text> m_text;

    std::shared_ptr<GameElement> m_Coin = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_CoinText = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_CoinImage = std::make_shared<GameElement>();
};

#endif
