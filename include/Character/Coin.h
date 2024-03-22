#include "GameElement.h"
#include "Util/Text.hpp"
#include <iostream>
#include <memory>

class Coin {
public:
    Coin();

    void setCoin();

    std::size_t getCoin();

    // return GameObject
    std::vector<std::shared_ptr<Util::GameObject>> getGameObject();

private:
    std::size_t m_Number = 0;
    std::size_t m_ZIndex = 50;
    std::size_t m_fontSize = 10;
    glm::vec2 m_Scale = {3, 3};
    std::string m_imagePath = ASSETS_DIR "/gui/hud_coins.png";
    std::string m_TextStylePath = ASSETS_DIR "/font/necrosans/necrosans.ttf";

    glm::vec2 m_Position = {575, 350};

    std::shared_ptr<Core::Drawable> m_text;

    std::shared_ptr<GameElement> m_CoinImage = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_CoinText = std::make_shared<GameElement>();
};
