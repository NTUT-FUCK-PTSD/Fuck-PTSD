//
// Created by adven on 2024/3/27.
//

#ifndef FUCK_PTSD_DISPLAY_H
#define FUCK_PTSD_DISPLAY_H

#include <iostream>

#include "ToolBoxs.h"
#include "GameElement.h"
#include "SpriteSheet.hpp"

class Display final {
public:
    explicit Display();
    ~Display();

    void Update();

    std::shared_ptr<GameElement> getGameElement() const { return m_BeatHeart; };
private:
    std::string m_HeartImagePath = ASSETS_DIR"/gui/TEMP_beat_heart.png";

    glm::vec2 m_Position = {0, 0};
    glm::vec2 m_Scale = {3, 3};
    std::size_t m_ZIndex = 50;

    std::shared_ptr<GameElement> m_BeatHeart = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_DISPLAY_H
