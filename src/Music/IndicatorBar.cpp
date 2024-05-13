#include "Music/IndicatorBar.h"
#include <algorithm>
#include <config.hpp>
#include <memory>
#include "Music/Music_config.h"
#include "Music/Tempo.h"
#include "UGameElement.h"
#include "Util/Logger.hpp"
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
    constexpr std::size_t WINDOW_WIDTH_HALF = WINDOW_WIDTH / 2;
    m_IIS = WINDOW_WIDTH_HALF / m_TempoNumber;
}

void Music::IndicatorBar::CreateImage() {
    m_IndicatorBlue = std::make_shared<Util::Image>(
        Music::Config::IMAGE_BLUE_INDICATOR.data()
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
        // LOG_INFO(m_IIS);
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

std::shared_ptr<Util::GameElement> Music::IndicatorBar::GetGameElement() {
    return m_GameElement;
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
        [idx = m_BeatIndex, intervalPixel, intervalTime](const auto& elem
        ) mutable {
            const auto&& tit = TempoIntervalTime(idx);
            const auto&& moveSpeed =
                MoveSpeed(intervalPixel, tit, intervalTime);

            const auto&  pos = elem->GetPosition();
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
        [idx = m_BeatIndex, intervalPixel, intervalTime](const auto& elem
        ) mutable {
            const auto&& tit = TempoIntervalTime(idx);
            const auto&& moveSpeed =
                MoveSpeed(intervalPixel, tit, intervalTime);

            const auto&  pos = elem->GetPosition();
            const auto&& x_pos = pos.x - moveSpeed;

            // LOG_INFO("idx: {}, pos: {}, speed:{}", idx, pos.x, moveSpeed);
            glm::ivec2 movePos = {0, 0};
            if (x_pos <= 0) {
                movePos = {720.0f + x_pos, m_CenterPos.y};
            } else {
                movePos = {x_pos, m_CenterPos.y};
            }
            elem->SetPosition(movePos);
            idx++;
        }
    ); /**
        * @note debug
        */
    // std::vector<std::size_t> list;
    // for (std::size_t i = 0; i < m_IndicatRight.size() - 1; i++) {
    //     const auto& fptr = [i]() {
    //         const auto& after = m_IndicatRight[i + 1]->GetPosition().x;
    //         const auto& before = m_IndicatRight[i]->GetPosition().x;

    //         if (after > before) {
    //             return after - before;
    //         } else if (after < before) {
    //             return (after) + (720 - before);
    //         }
    //     };

    //     list.push_back(fptr());

    //     //        LOG_INFO("index: {}, interval: {}", i, fptr());
    // }
    // const auto max = std::max_element(list.begin(), list.end());
    // const auto min = std::min_element(list.begin(), list.end());
    // LOG_INFO("max: {}, min: {}, time: {}", *max, *min, intervalTime);
    // list.clear();
}

namespace Music {
bool IndicatorBar::m_IsPause = false;

std::size_t                        IndicatorBar::m_IIT = 0;
std::size_t                        IndicatorBar::m_IIS = 0;
std::size_t                        IndicatorBar::m_BeatIndex = 0;
std::size_t                        IndicatorBar::m_LastRecordTime = 0;
std::size_t                        IndicatorBar::m_TempoNumber = 0;
std::shared_ptr<Util::Image>       IndicatorBar::m_IndicatorBlue = nullptr;
std::shared_ptr<Util::GameElement> IndicatorBar::m_GameElement = nullptr;
std::vector<std::shared_ptr<Util::GameElement>> IndicatorBar::m_IndicatLeft = {
};
std::vector<std::shared_ptr<Util::GameElement>> IndicatorBar::m_IndicatRight = {
};
}  // namespace Music
