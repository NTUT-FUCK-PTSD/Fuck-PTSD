#include "Display/BeatIndicator.h"

#include "Music/Tempo.h"

#include "Util/Image.hpp"
#include "Util/Time.hpp"

void Display::BeatIndicator::Init() {
    // init game element

    auto m_blueIndicator = std::make_shared<Util::Image>(
        ASSETS_DIR "/gui/TEMP_beat_marker.png"
    );
    m_GameElement = std::make_shared<GameElement>();
    m_GameElement->SetVisible(false);

    // count tempo number
    std::size_t counter = 0;
    for (; counter < Music::Tempo::GetBeatListLen(); ++counter) {
        if (Music::Tempo::GetBeatValue(counter) > 2000) {
            break;
        }
    }
    m_tempoNumber = counter;

    // create beat indicator object
    for (std::size_t i = 0; i < counter; i++) {
        auto object = std::make_shared<GameElement>();
        object->SetDrawable(m_blueIndicator);
        object->SetZIndex(99);
        object->SetScale({3.0, 2.5});
        object->SetPosition(m_Position);
        m_IndicatorList.push_back(object);

        m_GameElement->AddChild(object);
    }

    for (std::size_t i = 0; i < counter; i++) {
        auto object = std::make_shared<GameElement>();
        object->SetDrawable(m_blueIndicator);
        object->SetZIndex(99);
        object->SetScale({3.0, 2.5});
        object->SetPosition(m_Position);
        m_IndicatorListRight.push_back(object);

        m_GameElement->AddChild(object);
    }

    // init position
    auto intervalSpace = 720.0f / static_cast<float>(counter);

    auto position = m_Position;
    for (const auto& elem : m_IndicatorList) {
        elem->SetPosition(position);

        position.x -= intervalSpace;
    }

    position = m_Position;
    for (const auto& elem : m_IndicatorListRight) {
        elem->SetPosition(position);

        position.x += intervalSpace;
    }
}

void Display::BeatIndicator::Pause(bool state) {
    m_IsPause = state;
}

void Display::BeatIndicator::Update() {
    if (m_IsPause) {
        return;
    }

    auto currentTime = Util::Time::GetElapsedTimeMs();

    const auto intervalTime = currentTime - m_lastTime;
    m_lastTime = currentTime;

    // LOG_INFO(intervalTime);
    if (intervalTime >= 100) {
        return;
    }

    const auto intervalPixel = 720.0f / static_cast<float>(m_tempoNumber);

    std::size_t index = m_startBeatIndex;

    if (index + m_tempoNumber == Music::Tempo::GetBeatListLen()) {
        m_startBeatIndex = 0;
        return;
    }

    for (const auto& elem : m_IndicatorList) {
        const std::size_t tempoIntervalTime =
            Music::Tempo::GetBeatValue(index + 1)
            - Music::Tempo::GetBeatValue(index);

        const float&& moveSpeed = intervalPixel
                                  / (tempoIntervalTime / intervalTime);

        LOG_INFO(
            "value {}",

            moveSpeed

        );

        const auto position = elem->GetPosition();
        const auto movePosition = glm::vec2({position.x + moveSpeed, position.y}
        );

        index += 1;
        if (movePosition.x >= 0) {
            m_startBeatIndex += 1;
            elem->SetPosition({-720.0f, -310.0f});
            continue;
        }
        elem->SetPosition(movePosition);
    }

    index = m_startBeatIndex;
    for (const auto& elem : m_IndicatorListRight) {
        if (index + 1 == Music::Tempo::GetBeatListLen()) {
            m_startBeatIndex = 0;
            return;
        }
        const std::size_t tempoIntervalTime =
            Music::Tempo::GetBeatValue(index + 1)
            - Music::Tempo::GetBeatValue(index);
        const float moveSpeed = (intervalPixel
                                 / static_cast<float>(tempoIntervalTime))
                                * static_cast<float>(intervalTime);

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
std::size_t Display::BeatIndicator::m_startBeatIndex = 0;
std::size_t Display::BeatIndicator::m_tempoNumber = 0;
std::vector<std::shared_ptr<GameElement>>
    Display::BeatIndicator::m_IndicatorList = {};
std::vector<std::shared_ptr<GameElement>>
                             Display::BeatIndicator::m_IndicatorListRight = {};
std::shared_ptr<GameElement> Display::BeatIndicator::m_GameElement = {};
