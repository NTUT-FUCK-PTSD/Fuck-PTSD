//
// Created by adven on 2024/3/28.
//
#include "Music/Display.h"

Display::Display() {
    const auto HeartSize = ToolBoxs::CountImagePixel(m_HeartImagePath, 2, 1);

    m_TempoHeartImage = std::make_shared<SpriteSheet>(
        m_HeartImagePath, HeartSize, std::vector<std::size_t>{1, 0}, true, m_HeartInterval,
        false, 0);

    m_BeatHeart->SetDrawable(m_TempoHeartImage);
    m_BeatHeart->SetPosition(m_Position);
    m_BeatHeart->SetScale(m_Scale);
    m_BeatHeart->SetZIndex(m_ZIndex);
}

Display::~Display() {}

void Display::Update(std::size_t time, std::size_t triggerTime) {

    if (time - 50 >= triggerTime - 100 && time - 50 <= triggerTime + 100) {
        m_TempoHeartImage->Play();
    }
}
