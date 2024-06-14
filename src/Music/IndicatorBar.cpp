#include "Music/IndicatorBar.h"

#include <algorithm>
#include <config.hpp>
#include <memory>
#include "glm/fwd.hpp"

#include "Animation.h"
#include "Music/Music_config.h"
#include "Music/Player.h"
#include "Music/Tempo.h"
#include "UGameElement.h"
#include "Util/Time.hpp"

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
    auto WINDOW_WIDTH_HALF = PTSD_Config::WINDOW_WIDTH >> 1;
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
        m_AnimationsLeft.push_back(
            std::make_shared<Animation>(object->GetPosition())
        );
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
        m_AnimationsRight.push_back(
            std::make_shared<Animation>(object->GetPosition())
        );
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

    // Get m_BeatIndex
    m_BeatIndex = Music::Tempo::GetBeatIdx();
    // LOG_INFO("beat index: {}", m_BeatIndex);

    UpdateTimer();
    if (m_IIT >= FRAME_UPDATE_MAX) { return; }

    UpdateIndicatorLeft(m_BeatIndex, m_IIT, m_IIS);
    UpdateIndicatorRight(m_BeatIndex, m_IIT, m_IIS);

    if (m_BeatIndex + m_TempoNumber >= Music::Tempo::GetBeatListLen()) {
        m_BeatIndex = 0;
    }
    // else if (Music::Tempo::GetBeatIdx() != m_BeatIndex) {
    //     m_BeatIndex++;
    // }
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
    // LOG_INFO(
    //     "{} {}",
    //     Music::Player::GetMusicTime() * 1000,
    //     Music::Tempo::GetBeatValue(index)
    // );
    for (std::size_t i = 0; i < m_AnimationsLeft.size(); i++) {
        if (m_AnimationsLeft[i]->UpdateAnimation()) {
            m_IndicatLeft[i]->SetPosition(
                m_AnimationsLeft[i]->GetAnimationPosition()
            );
        } else {
            m_AnimationsLeft[i]->SetAnimationPosition({-720.f, m_CenterPos.y});
            // m_IndicatLeft[i]->SetPosition({-720.0f, m_CenterPos.y});
            m_AnimationsLeft[i]->MoveByTime(
                Music::Tempo::GetBeatValue(m_LastIdxLeft)
                    - Music::Player::GetMusicTime() * 1000,
                {0, m_CenterPos.y}
            );
            m_LastIdxLeft++;
        }
    }
    // std::for_each(
    //     m_IndicatLeft.begin(),
    //     m_IndicatLeft.end(),
    //     [idx = m_BeatIndex, intervalPixel, intervalTime](const auto& elem
    //     ) mutable {
    //         const auto&& tit = TempoIntervalTime(idx);
    //         const auto&& moveSpeed =
    //             MoveSpeed(intervalPixel, tit, intervalTime);

    //         const auto&  pos = elem->GetPosition();
    //         const auto&& x_pos = pos.x + moveSpeed;

    //         glm::ivec2 movePos = {0, 0};
    //         if (x_pos >= 0) {
    //             movePos = {-720.0f + x_pos, m_CenterPos.y};
    //         } else {
    //             movePos = {x_pos, m_CenterPos.y};
    //         }
    //         elem->SetPosition(movePos);
    //         idx++;
    //     }
    // );
}

void Music::IndicatorBar::UpdateIndicatorRight(
    std::size_t index,
    std::size_t intervalTime,
    std::size_t intervalPixel
) {
    for (std::size_t i = 0; i < m_AnimationsRight.size(); i++) {
        if (m_AnimationsRight[i]->UpdateAnimation()) {
            m_IndicatRight[i]->SetPosition(
                m_AnimationsRight[i]->GetAnimationPosition()
            );
        } else {
            m_AnimationsRight[i]->SetAnimationPosition({720.f, m_CenterPos.y});
            // m_IndicatRight[i]->SetPosition({-720.0f, m_CenterPos.y});
            m_AnimationsRight[i]->MoveByTime(
                Music::Tempo::GetBeatValue(m_LastIdxRight)
                    - Music::Player::GetMusicTime() * 1000,
                {0, m_CenterPos.y}
            );
            m_LastIdxRight++;
        }
    }
    // std::for_each(
    //     m_IndicatRight.begin(),
    //     m_IndicatRight.end(),
    //     [idx = m_BeatIndex, intervalPixel, intervalTime](const auto& elem
    //     ) mutable {
    //         const auto&& tit = TempoIntervalTime(idx);
    //         const auto&& moveSpeed =
    //             MoveSpeed(intervalPixel, tit, intervalTime);

    //         const auto&  pos = elem->GetPosition();
    //         const auto&& x_pos = pos.x - moveSpeed;

    //         // LOG_INFO("idx: {}, pos: {}, speed:{}", idx, pos.x, moveSpeed);
    //         glm::ivec2 movePos = {0, 0};
    //         if (x_pos <= 0) {
    //             movePos = {720.0f + x_pos, m_CenterPos.y};
    //         } else {
    //             movePos = {x_pos, m_CenterPos.y};
    //         }
    //         elem->SetPosition(movePos);
    //         idx++;
    //     }
    // ); /**
    // *@note debug* /
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

void Music::IndicatorBar::Reset() {
    if (m_GameElement == nullptr || m_IndicatorBlue == nullptr) { return; }
    auto idx = Music::Tempo::GetBeatIdx();
    m_IIT = 0;
    m_IIS = 0;
    m_BeatIndex = idx;
    m_LastRecordTime = 0;
    m_TempoNumber = 0;
    m_GameElement->ClearChildren();
    m_IndicatLeft.clear();
    m_IndicatRight.clear();
    m_AnimationsLeft.clear();
    m_AnimationsRight.clear();
    m_LastIdxLeft = idx;
    m_LastIdxRight = idx;
    CountTempoNumber();
    CountIndicatorIntervalSpace();
    CreateIndicatorLeft();
    CreateIndicatorRight();
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
std::vector<std::shared_ptr<Animation>> Music::IndicatorBar::m_AnimationsLeft;
std::vector<std::shared_ptr<Animation>> Music::IndicatorBar::m_AnimationsRight;
std::size_t                             Music::IndicatorBar::m_LastIdxLeft = 0;
std::size_t                             Music::IndicatorBar::m_LastIdxRight = 0;
