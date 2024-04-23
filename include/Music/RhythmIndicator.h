//
// Created by adven on 2024/4/19.
//

#ifndef FUCK_PTSD_RHYTHMINDICATOR_H
#define FUCK_PTSD_RHYTHMINDICATOR_H

#include <iostream>

#include "GameElement.h"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

namespace Music {

class RhythmIndicator final {
public:
    explicit RhythmIndicator();

    void SetTempoTriggerList(std::vector<std::size_t> tempoTriggerList);

    std::shared_ptr<GameElement> GetGameElement();

    void Update();

private:
    // functions
    void        CreateGameElement(std::size_t number);
    void        InitIndicationPosition();
    std::size_t CountTempoNumber(std::size_t second);

    // settings
    const std::size_t m_tempoRange = 2000;  // 2 sec
    std::size_t       m_startBeatIndex = 0;
    std::size_t       m_tempoNumber = 0;
    std::size_t       m_lastTime = 0;

    std::vector<std::size_t> m_tempoTriggerList;

    // graph
    const glm::vec2 m_centerPosition = {0, -310};

    std::shared_ptr<GameElement>              m_rhythmIndicator;
    std::vector<std::shared_ptr<GameElement>> m_IndicatorList;
    std::vector<std::shared_ptr<GameElement>> m_IndicatorListLeft;

    std::shared_ptr<Util::Image> m_redIndicator;
    std::shared_ptr<Util::Image> m_blueIndicator;
    std::shared_ptr<Util::Image> m_greenIndicator;
};
}  // namespace Music

#endif  // FUCK_PTSD_RHYTHMINDICATOR_H
