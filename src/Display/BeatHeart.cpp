#include "Display/BeatHeart.h"

#include "Util/Time.hpp"
#include "config.hpp"

#include "Settings/Window.hpp"
#include "ToolBoxs.h"

void Display::BeatHeart::Init() {
    glm::vec2 position = {
      0,
      -(static_cast<int>(PTSD_Config::WINDOW_HEIGHT >> 1))
          + (52 * Window::Scale) / 2 + Window::TileWidth
    };
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
    m_GameElement->SetPosition(position);
    m_GameElement->SetScale(Window::GetScale());
    m_GameElement->SetZIndex(m_ZIndex);
}

void Display::BeatHeart::Pause(bool state) {
    m_IsPause = state;
}

void Display::BeatHeart::SwitchHeart(const std::size_t duringTime) {
    m_AfterSwitchTime = Util::Time::GetElapsedTimeMs() + duringTime;

    m_HeartImage->SetCurrentFrame(1);
}

void Display::BeatHeart::Update() {
    if (m_IsPause) { return; }

    if (Util::Time::GetElapsedTimeMs() > m_AfterSwitchTime) {
        m_HeartImage->SetCurrentFrame(0);
    }
}

std::shared_ptr<GameElement> Display::BeatHeart::GetGameElement() {
    return m_GameElement;
}

bool                         Display::BeatHeart::m_IsPause = false;
float                        Display::BeatHeart::m_ZIndex = 100;
std::size_t                  Display::BeatHeart::m_AfterSwitchTime = 0;
std::shared_ptr<SpriteSheet> Display::BeatHeart::m_HeartImage = nullptr;

std::shared_ptr<GameElement> Display::BeatHeart::m_GameElement =
    std::make_shared<GameElement>();

std::string Display::BeatHeart::m_HeartImagePath = ASSETS_DIR
    "/gui/TEMP_beat_heart.png";
