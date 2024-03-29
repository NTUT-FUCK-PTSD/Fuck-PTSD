//
// Created by adven on 2024/3/28.
//
#include "Music/Display.h"

Display::Display() {
    const auto HeartSize = ToolBoxs::CountImagePixel(m_HeartImagePath, 2, 1);

    m_TempoHeartImage = std::make_shared<SpriteSheet>(
        m_HeartImagePath, HeartSize, std::vector<std::size_t>{0, 1}, true,
        m_HeartInterval, false, 0);

    m_BeatHeart->SetDrawable(m_TempoHeartImage);
    m_BeatHeart->SetPosition(m_Position);
    m_BeatHeart->SetScale(m_Scale);
    m_BeatHeart->SetZIndex(m_ZIndex);
}

Display::~Display() {}

void Display::Update() {

    // update the heart beat
    if (m_CurrentMusicTime + m_offset > m_triggerTime + m_heartBeatTime) {
        m_TempoHeartImage->SetCurrentFrame(0);
    } else if (m_CurrentMusicTime + m_offset > m_triggerTime) {
        m_TempoHeartImage->SetCurrentFrame(1);
    }
}
