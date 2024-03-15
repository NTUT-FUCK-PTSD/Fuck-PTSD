//
// Created by adven on 2024/3/6.
//

#ifndef FUCK_PTSD_ANIMATION_H
#define FUCK_PTSD_ANIMATION_H

#include "MainCharacter.h"
#include "Util/Time.hpp"

namespace Animation {
bool move_player(std::shared_ptr<std::int16_t> animationPass,
                 unsigned long firstTime, MainCharacter::Direction direction,
                 std::shared_ptr<MainCharacter> player);
glm::vec2 moveCameraByTime(unsigned long firstTimeMs, unsigned long lastTimeMs,
                           glm::vec2 destination, glm::vec2 cameraPosition);
bool movePlayerByTime(unsigned long firstTimeMs, unsigned long lastTimeMs,
                      glm::vec2 destination,
                      std::shared_ptr<MainCharacter> player);
} // namespace Animation

#endif // FUCK_PTSD_ANIMATION_H
