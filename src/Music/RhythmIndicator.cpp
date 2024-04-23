//
// Created by adven on 2024/4/19.
//

#include "Music/RhythmIndicator.h"

Music::RhythmIndicator::RhythmIndicator()
    : m_rhythmIndicator(std::make_shared<GameElement>()),
      m_redIndicator(std::make_shared<Util::Image>(
          ASSETS_DIR "/gui/TEMP_beat_marker_red.png"
      )),
      m_blueIndicator(
          std::make_shared<Util::Image>(ASSETS_DIR "/gui/TEMP_beat_marker.png")
      ),
      m_greenIndicator(std::make_shared<Util::Image>(
          ASSETS_DIR "/gui/TEMP_beat_marker_green.png"
      )) {
    //    m_rhythmIndicator->SetVisible(false);
}

std::shared_ptr<GameElement> Music::RhythmIndicator::GetGameElement() {
    return m_rhythmIndicator;
}

void Music::RhythmIndicator::SetTempoTriggerList(
    std::vector<std::size_t> tempoTriggerList
) {
    m_tempoTriggerList = std::move(tempoTriggerList);
    m_tempoNumber = CountTempoNumber(m_tempoRange);

    CreateGameElement(m_tempoNumber);
    InitIndicationPosition();
}

void Music::RhythmIndicator::Update() {
    auto currentTime = Util::Time::GetElapsedTimeMs();

    const auto intervalTime = currentTime - m_lastTime;
    m_lastTime = currentTime;

    // LOG_INFO(intervalTime);
    if (intervalTime >= 100) {
        return;
    }

    const auto intervalPixel = 720.0f / static_cast<float>(m_tempoNumber);

    std::size_t index = m_startBeatIndex;

    if (index + m_tempoNumber == m_tempoTriggerList.size()) {
        m_startBeatIndex = 0;
        return;
    }

    for (const auto& elem : m_IndicatorList) {
        const std::size_t tempoIntervalTime = m_tempoTriggerList[index + 1]
                                              - m_tempoTriggerList[index];
        const float moveSpeed = (intervalPixel
                                 / static_cast<float>(tempoIntervalTime))
                                * static_cast<float>(intervalTime);

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
    for (const auto& elem : m_IndicatorListLeft) {
        const std::size_t tempoIntervalTime = m_tempoTriggerList[index + 1]
                                              - m_tempoTriggerList[index];
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

std::size_t Music::RhythmIndicator::CountTempoNumber(std::size_t second) {
    std::size_t index = 0;
    for (std::size_t trigger : m_tempoTriggerList) {
        if (trigger >= second) {
            return index;
        }
        index++;
    }
    return index;
}

void Music::RhythmIndicator::CreateGameElement(std::size_t number) {
    for (std::size_t i = 0; i < number; i++) {
        auto object = std::make_shared<GameElement>();
        object->SetDrawable(m_blueIndicator);
        object->SetZIndex(99);
        object->SetScale({3.0, 2.5});
        object->SetPosition(m_centerPosition);
        m_IndicatorList.push_back(object);

        m_rhythmIndicator->AddChild(object);
    }

    for (std::size_t i = 0; i < number; i++) {
        auto object = std::make_shared<GameElement>();
        object->SetDrawable(m_blueIndicator);
        object->SetZIndex(99);
        object->SetScale({3.0, 2.5});
        object->SetPosition(m_centerPosition);
        m_IndicatorListLeft.push_back(object);

        m_rhythmIndicator->AddChild(object);
    }
}

void Music::RhythmIndicator::InitIndicationPosition() {
    auto intervalSpace = 720.0f / static_cast<float>(m_tempoNumber);

    auto position = m_centerPosition;
    for (const auto& elem : m_IndicatorList) {
        elem->SetPosition(position);

        position.x -= intervalSpace;
    }

    position = m_centerPosition;
    for (const auto& elem : m_IndicatorListLeft) {
        elem->SetPosition(position);

        position.x += intervalSpace;
    }
}
