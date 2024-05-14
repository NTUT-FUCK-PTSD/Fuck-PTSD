#include "Display/BeatIndicator.h"

#include "Music/Tempo.h"

#include <memory>
#include "Music/Player.h"
#include "Util/Image.hpp"
#include "Util/Time.hpp"

auto CountTempoNumber = []() -> std::size_t {
    for (std::size_t index = 0; index < Music::Tempo::GetBeatListLen();
         index++) {
        if (Music::Tempo::GetBeatValue(index) > 2000) { return index; }
    }
    return 0;
};

void Display::BeatIndicator::GenLeftIndicator(std::size_t counter) {
    for (std::size_t i = 0; i < counter; i++) {
        auto object = std::make_shared<GameElement>();
        object->SetDrawable(m_blueIndicator);
        object->SetZIndex(99);
        object->SetScale({3.0, 2.5});
        object->SetPosition(m_Position);
        m_IndicatorList.push_back(object);
        m_GameElement->AddChild(object);
    }
    auto position = m_Position;
    for (const auto& elem : m_IndicatorList) {
        elem->SetPosition(position);

        position.x -= m_intervalSpace;
    }
}

void Display::BeatIndicator::GenRightIndicator(std::size_t counter) {
    for (std::size_t i = 0; i < counter; i++) {
        auto object = std::make_shared<GameElement>();
        object->SetDrawable(m_blueIndicator);
        object->SetZIndex(99);
        object->SetScale({3.0, 2.5});
        object->SetPosition(m_Position);
        m_IndicatorListRight.push_back(object);
        m_GameElement->AddChild(object);
    }

    auto position = m_Position;
    for (const auto& elem : m_IndicatorListRight) {
        elem->SetPosition(position);

        position.x += m_intervalSpace;
    }
}

void Display::BeatIndicator::Init() {
    CreateImage();
    m_tempoNumber = CountTempoNumber();
    m_intervalSpace = 720.0f / static_cast<float>(m_tempoNumber);

    GenLeftIndicator(m_tempoNumber);
    GenRightIndicator(m_tempoNumber);
}

void Display::BeatIndicator::CreateImage() {
    // init game element
    m_blueIndicator = std::make_shared<Util::Image>(ASSETS_DIR
                                                    "/gui/TEMP_beat_marker.png"
    );
    m_GameElement = std::make_shared<GameElement>();
    m_GameElement->SetVisible(false);
}

void Display::BeatIndicator::Pause(bool state) {
    m_IsPause = state;
}

void Display::BeatIndicator::Update() {
    if (m_IsPause) { return; }

    auto currentTime = Util::Time::GetElapsedTimeMs();

    const auto intervalTime = currentTime - m_lastTime;
    m_lastTime = currentTime;

    // LOG_INFO(intervalTime);
    if (intervalTime >= 100) { return; }

    const auto intervalPixel = 720.0f / static_cast<float>(m_tempoNumber);
    UpdateLeftIndi(m_startBeatIndex, intervalTime, intervalPixel);
    UpdateRightIndi(m_startBeatIndex, intervalTime, intervalPixel);

    std::size_t index = m_startBeatIndex;

    if (index + m_tempoNumber == Music::Tempo::GetBeatListLen()) {
        m_startBeatIndex = 0;
        return;
    }

    //    LOG_INFO(m_startBeatIndex);

    if (Music::Tempo::GetBeatIdx() != m_beatIdx) {
        m_beatIdx = Music::Tempo::GetBeatIdx();
        m_startBeatIndex++;
    }
}

void Display::BeatIndicator::UpdateLeftIndi(
    std::size_t index,
    std::size_t intervalTime,
    std::size_t intervalPixel
) {
    std::size_t index_t = index;
    for (const auto& elem : m_IndicatorList) {
        const std::size_t tempoIntervalTime =
            Music::Tempo::GetBeatValue(index + 1)
            - Music::Tempo::GetBeatValue(index);

        const std::size_t&& moveSpeed =
            (static_cast<long double>(intervalPixel)
             / static_cast<long double>(tempoIntervalTime))
            * intervalTime;

        const auto t =
            (static_cast<long double>(intervalPixel)
             / static_cast<long double>(tempoIntervalTime));

        //        LOG_DEBUG(
        //            "move: {}, {}, {}",
        //            intervalPixel,
        //            tempoIntervalTime,
        //            intervalTime
        //        );

        //        const std::size_t moveSpeed = (intervalPixel
        //                                       /
        //                                       static_cast<float>(tempoIntervalTime))
        //                                      * static_cast<float>(intervalTime);

        const auto position = elem->GetPosition();
        auto movePosition = glm::vec2({position.x + moveSpeed, position.y});

        //        LOG_INFO(
        //            "{} {} {}",
        //            Music::Player::GetMusicTimeLoop(),
        //            Music::Tempo::GetBeatValue(index_t),
        //            index_t
        //        );

        if (movePosition.x >= 0) {
            movePosition =
                glm::ivec2{-720.0f + moveSpeed + position.x, -310.0f};
            //            elem->SetPosition({-720.0f, -310.0f});
        }
        elem->SetPosition(movePosition);

        index_t++;
    }

    /**
     * @note debug
     */
    std::vector<std::size_t> list;
    for (std::size_t i = 0; i < m_IndicatorList.size() - 1; i++) {
        const auto& fptr = [i]() {
            const auto& after = m_IndicatorList[i + 1]->GetPosition().x;
            const auto& before = m_IndicatorList[i]->GetPosition().x;

            if (after < before) {
                return after - before;
            } else if (after > before) {
                return (after) + (-720 - before);
            }
        };

        list.push_back(-fptr());

        //        LOG_INFO("index: {}, interval: {}", i, fptr());
    }
    const auto max = std::max_element(list.begin(), list.end());
    const auto min = std::min_element(list.begin(), list.end());

    list.clear();
}

void Display::BeatIndicator::UpdateRightIndi(
    std::size_t index,
    std::size_t intervalTime,
    std::size_t intervalPixel
) {
    for (const auto& elem : m_IndicatorListRight) {
        if (index + 1 == Music::Tempo::GetBeatListLen()) {
            m_startBeatIndex = 0;
            return;
        }
        const std::size_t tempoIntervalTime =
            Music::Tempo::GetBeatValue(index + 1)
            - Music::Tempo::GetBeatValue(index);
        //        const float moveSpeed = (intervalPixel
        //                                 /
        //                                 static_cast<float>(tempoIntervalTime))
        //                                * static_cast<float>(intervalTime);
        const std::size_t&& moveSpeed =
            (static_cast<long double>(intervalPixel)
             / static_cast<long double>(tempoIntervalTime))
            * intervalTime;

        const auto position = elem->GetPosition();
        const auto movePosition = glm::vec2({position.x - moveSpeed, position.y}
        );

        index += 1;
        if (movePosition.x <= 0) {
            //            m_startBeatIndex += 1;
            elem->SetPosition({720.0f, -310.0f});
            continue;
        }
        elem->SetPosition(movePosition);
    }
}

std::shared_ptr<GameElement> Display::BeatIndicator::GetGameElement() {
    return m_GameElement;
}

bool        Display::BeatIndicator::m_IsPause = false;
std::string Display::BeatIndicator::m_IndicatorImagePath = "";
glm::vec2   Display::BeatIndicator::m_Position = {0, -310};
// glm::vec2   Display::BeatIndicator::m_Scale;
// float       Display::BeatIndicator::m_ZIndex;
std::size_t Display::BeatIndicator::m_lastTime = 0;
std::size_t Display::BeatIndicator::m_beatIdx = 0;
std::size_t Display::BeatIndicator::m_startBeatIndex = 0;
std::size_t Display::BeatIndicator::m_intervalSpace = 0;
std::size_t Display::BeatIndicator::m_tempoNumber = 0;
std::vector<std::shared_ptr<GameElement>>
    Display::BeatIndicator::m_IndicatorList = {};
std::vector<std::shared_ptr<GameElement>>
                             Display::BeatIndicator::m_IndicatorListRight = {};
std::shared_ptr<GameElement> Display::BeatIndicator::m_GameElement = {};
std::shared_ptr<Util::Image> Display::BeatIndicator::m_blueIndicator = nullptr;
