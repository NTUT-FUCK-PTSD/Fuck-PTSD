#include "Display/BeatHeart.h"

#include "Util/Time.hpp"

#include "ToolBoxs.h"

void Display::BeatHeart::Init() {
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

    m_GameElement->SetDrawable(m_HeartImage);
    m_GameElement->SetPosition(m_Position);
    m_GameElement->SetScale(m_Scale);
    m_GameElement->SetZIndex(m_ZIndex);
}

void Display::BeatHeart::SwitchHeart(const std::size_t duringTime) {
    m_AfterSwitchTime = Util::Time::GetElapsedTimeMs() + duringTime;

    m_HeartImage->SetCurrentFrame(1);
}

void Display::BeatHeart::Update() {
    if (Util::Time::GetElapsedTimeMs() > m_AfterSwitchTime) {
        m_HeartImage->SetCurrentFrame(0);
    }
}

std::shared_ptr<GameElement> Display::BeatHeart::GetGameElement() {
    return m_GameElement;
}

std::shared_ptr<GameElement> Display::BeatHeart::m_GameElement =
    std::make_shared<GameElement>();

std::shared_ptr<SpriteSheet> Display::BeatHeart::m_HeartImage = nullptr;

std::string Display::BeatHeart::m_HeartImagePath = ASSETS_DIR
    "/gui/TEMP_beat_heart.png";

glm::vec2 Display::BeatHeart::m_Position = {
  0,
  -(static_cast<int>(WINDOW_HEIGHT) / 2) + (52 * DUNGEON_SCALE) / 2
      + DUNGEON_TILE_WIDTH
};

glm::vec2 Display::BeatHeart::m_Scale = {DUNGEON_SCALE, DUNGEON_SCALE};

float Display::BeatHeart::m_ZIndex = 100;

std::size_t Display::BeatHeart::m_AfterSwitchTime = 0;
