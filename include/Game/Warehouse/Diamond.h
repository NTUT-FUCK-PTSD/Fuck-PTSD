#ifndef FUCK_PTSD_DIAMOND_H
#define FUCK_PTSD_DIAMOND_H

#include "config.hpp"

#include <iostream>
#include <memory>
#include "GameElement.h"
#include "Util/Text.hpp"

class Diamond {
public:
    Diamond();

    virtual ~Diamond() = default;

    void plusDiamondNumber(const int number);

    std::size_t getDiamond();

    // return GameObject
    std::vector<std::shared_ptr<Util::GameObject>> getGameObject();
    std::shared_ptr<GameElement>                   GetGameObject();

private:
    void toLeftSideDiamondText();

    std::size_t m_Number = 0;
    std::size_t m_ZIndex = 100;
    std::size_t m_fontSize = 6;
    glm::vec2   m_ImageScale = {3, 3};
    glm::vec2   m_FontScale = {5, 5};
    std::string m_showText = "*0";
    std::string m_imagePath = ASSETS_DIR "/gui/diamond.png";
    //    std::string m_TextStylePath = ASSETS_DIR
    //    "/font/necrosans/necrosans.ttf";
    std::string m_TextStylePath = ASSETS_DIR
        "/font/necrosans-6/necrosans-6.otf";

    glm::vec2 m_Position = {WINDOW_WIDTH / 2 - 135, WINDOW_HEIGHT / 2 - 130};

    std::shared_ptr<Util::Text> m_text;

    std::shared_ptr<GameElement> m_DiamondImage = std::make_shared<GameElement>(
    );
    std::shared_ptr<GameElement> m_DiamondText = std::make_shared<GameElement>(
    );
    std::shared_ptr<GameElement> m_Diamond = std::make_shared<GameElement>();
};
#endif
