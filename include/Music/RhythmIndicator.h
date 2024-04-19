//
// Created by adven on 2024/4/19.
//

#ifndef FUCK_PTSD_RHYTHMINDICATOR_H
#define FUCK_PTSD_RHYTHMINDICATOR_H

#include <iostream>
#include "Util/Image.hpp"
#include "GameElement.h"

namespace Music {
class RhythmIndicator final {
public:
    explicit RhythmIndicator();

    std::shared_ptr<GameElement> GetGameElement();

    void Update();
private:


    const glm::vec2 m_centerPosition = {0, -300};

    std::shared_ptr<GameElement> m_rhythmIndicator;

    std::shared_ptr<Util::Image> m_redIndicator;
    std::shared_ptr<Util::Image> m_blueIndicator;
    std::shared_ptr<Util::Image> m_greenIndicator;

};
}

#endif // FUCK_PTSD_RHYTHMINDICATOR_H
