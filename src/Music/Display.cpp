//
// Created by adven on 2024/3/28.
//
#include "Music/Display.h"

Display::Display() {
    const auto HeartSize = ToolBoxs::CountImagePixel(m_HeartImagePath, 2, 1);

    const auto HeartImage = std::make_shared<SpriteSheet>(
        m_HeartImagePath, HeartSize, std::vector<std::size_t>{0, 1}, false,
        100, false, 100);

    m_BeatHeart->SetDrawable(HeartImage);
    m_BeatHeart->SetPosition(m_Position);
    m_BeatHeart->SetScale(m_Scale);
    m_BeatHeart->SetZIndex(m_ZIndex);
}

Display::~Display() {}

void Display::Update() {}
