#include "Display/BeatHeart.h"

#include <iostream>
#include <memory>

#include "SpriteSheet.hpp"
#include "ToolBoxs.h"

Display::BeatHeart::BeatHeart() {
    const auto HeartSize = ToolBoxs::CountImagePixel(m_HeartImagePath, 2, 1);

    m_HeartImage = std::make_shared<SpriteSheet>(
        m_HeartImagePath,
        HeartSize,
        std::vector<std::size_t>{0, 1},
        true,
        10,
        false,
        0
    );

    SetDrawable(m_HeartImage);
    SetPosition(m_Position);
    SetScale(m_Scale);
    SetZIndex(m_ZIndexBeatHeart);
}

void Display::BeatHeart::Update() {
    // update the heart beat
    if (m_CurrentMusicTime + m_offset > m_triggerTime + m_heartBeatTime) {
        m_TempoHeartImage->SetCurrentFrame(0);
    } else if (m_CurrentMusicTime + m_offset > m_triggerTime) {
        m_TempoHeartImage->SetCurrentFrame(1);
    }
}

std::string Display::BeatHeart::m_HeartImagePath = ASSETS_DIR
    "/gui/TEMP_beat_heart.png";

std::shared_ptr<SpriteSheet> Display::BeatHeart::m_HeartImage = nullptr;
