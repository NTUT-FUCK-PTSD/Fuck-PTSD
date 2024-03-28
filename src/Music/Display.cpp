//
// Created by adven on 2024/3/28.
//
#include "Music/Display.h"

Display::Display() {
    const auto HeartSize = ToolBoxs::CountImagePixel(m_HeartImagePath, 2, 1);

    m_TempoHeartImage = std::make_shared<SpriteSheet>(
        m_HeartImagePath, HeartSize, std::vector<std::size_t>{1, 0}, true,
        m_HeartInterval, false, 0);

    m_BeatHeart->SetDrawable(m_TempoHeartImage);
    m_BeatHeart->SetPosition(m_Position);
    m_BeatHeart->SetScale(m_Scale);
    m_BeatHeart->SetZIndex(m_ZIndex);
}

Display::~Display() {}

void Display::Update() {

    if (m_CurrentMusicTime >= m_triggerTime - m_range &&
        m_CurrentMusicTime <= m_triggerTime + m_range) {
        m_TempoHeartImage->Play();
    }
}
