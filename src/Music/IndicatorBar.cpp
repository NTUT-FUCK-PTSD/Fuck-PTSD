#include "Music/IndicatorBar.h"
#include <algorithm>
#include <config.hpp>
#include <memory>
#include "Music/Music_config.h"
#include "Music/Tempo.h"
#include "UGameElement.h"
#include "Util/Time.hpp"
#include "glm/fwd.hpp"

void Music::IndicatorBar::Init() {
    CountTempoNumber();
    CountIndicatorIntervalSpace();

    CreateImage();
    CreateIndicatorLeft();
    CreateIndicatorRight();
}

void Music::IndicatorBar::CountTempoNumber() {
    const std::size_t maxLen = Music::Tempo::GetBeatListLen();
    for (std::size_t index = 0; index < maxLen; index++) {
        if (Music::Tempo::GetBeatValue(index) > TEMPO_TIME_RANGE) {
            m_TempoNumber = index;
            break;
        }
    }
}

void Music::IndicatorBar::CountIndicatorIntervalSpace() {
    m_IIS = WINDOW_WIDTH / m_TempoNumber;
}

void Music::IndicatorBar::CreateImage() {
    m_IndicatorBlue = std::make_shared<Util::Image>(
        Music::Config::IMAGE_BLUE_INDICATOR
    );
    m_GameElement = std::make_shared<Util::GameElement>();
    m_GameElement->SetVisible(false);
}

void Music::IndicatorBar::CreateIndicatorLeft() {
    for (std::size_t i = 0; i < m_TempoNumber; i++) {
        auto object = std::make_shared<Util::GameElement>();
        object->SetDrawable(m_IndicatorBlue);
        object->SetZIndex(99);
        object->SetScale({3.0, 2.5});
        object->SetPosition({0, 0});
        m_IndicatLeft.push_back(object);
        m_GameElement->AddChild(object);
    }

    auto position = m_CenterPos;
    for (const auto& elem : m_IndicatLeft) {
        elem->SetPosition(position);

        position.x -= m_IIS;
    }
}

void Music::IndicatorBar::CreateIndicatorRight() {
    for (std::size_t i = 0; i < m_TempoNumber; i++) {
        auto object = std::make_shared<Util::GameElement>();
        object->SetDrawable(m_IndicatorBlue);
        object->SetZIndex(99);
        object->SetScale({3.0, 2.5});
        object->SetPosition({0, 0});
        m_IndicatRight.push_back(object);
        m_GameElement->AddChild(object);
    }

    auto position = m_CenterPos;
    for (const auto& elem : m_IndicatRight) {
        elem->SetPosition(position);

        position.x += m_IIS;
    }
}

void Music::IndicatorBar::Pause(bool state) {
    m_IsPause = state;
}

void Music::IndicatorBar::UpdateTimer() {
    const auto&& current = Util::Time::GetElapsedTimeMs();
    const auto&& diff = current - m_LastRecordTime;
    m_LastRecordTime = current;

    m_IIT = diff;
}

void Music::IndicatorBar::Update() {
    if (m_IsPause) { return; }

    UpdateTimer();
    if (m_IIT >= FRAME_UPDATE_MAX) { return; }

    UpdateIndicatorLeft(m_BeatIndex, m_IIT, m_IIS);
    UpdateIndicatorRight(m_BeatIndex, m_IIT, m_IIS);

    if (m_BeatIndex + m_TempoNumber >= Music::Tempo::GetBeatListLen()) {
        m_BeatIndex = 0;
    } else if (Music::Tempo::GetBeatIdx() != m_BeatIndex) {
        m_BeatIndex++;
    }
}

const auto TempoIntervalTime = [](std::size_t idx) {
    return Music::Tempo::GetBeatValue(idx + 1)
           - Music::Tempo::GetBeatValue(idx);
};

const auto MoveSpeed = [](std::size_t iis, std::size_t tit, std::size_t iit) {
    return (static_cast<float>(iis) / static_cast<float>(tit)) * iit;
};

void Music::IndicatorBar::UpdateIndicatorLeft(
    std::size_t index,
    std::size_t intervalTime,
    std::size_t intervalPixel
) {
    std::for_each(
        m_IndicatLeft.begin(),
        m_IndicatLeft.end(),
        [idx = 0, intervalPixel, intervalTime](const auto& elem) mutable {
            const auto&& tit = TempoIntervalTime(idx);
            const auto&& moveSpeed =
                MoveSpeed(intervalPixel, tit, intervalTime);

            const auto&& pos = elem->GetPosition();
            const auto&& x_pos = pos.x + moveSpeed;

            glm::ivec2 movePos = {0, 0};
            if (x_pos >= 0) {
                movePos = {-720.0f + x_pos, m_CenterPos.y};
            } else {
                movePos = {x_pos, m_CenterPos.y};
            }
            elem->SetPosition(movePos);
            idx++;
        }
    );
}

void Music::IndicatorBar::UpdateIndicatorRight(
    std::size_t index,
    std::size_t intervalTime,
    std::size_t intervalPixel
) {
    std::for_each(
        m_IndicatRight.begin(),
        m_IndicatRight.end(),
        [idx = 0, intervalPixel, intervalTime](const auto& elem) mutable {
            const auto&& tit = TempoIntervalTime(idx);
            const auto&& moveSpeed =
                MoveSpeed(intervalPixel, tit, intervalTime);

            const auto&& pos = elem->GetPosition();
            const auto&& x_pos = pos.x - moveSpeed;

            glm::ivec2 movePos = {0, 0};
            if (x_pos <= 0) {
                movePos = {720.0f - x_pos, m_CenterPos.y};
            } else {
                movePos = {x_pos, m_CenterPos.y};
            }
            elem->SetPosition(movePos);
            idx++;
        }
    );
}

namespace Music {
bool        m_IsPause = false;
std::size_t IndicatorBar::m_TempoNumber = 0;
std::size_t m_BeatIndex = 0;
std::size_t m_LastRecordTime = 0;
std::size_t m_IIT = 0;
}  // namespace Music
