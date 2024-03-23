//
// Created by adven on 2024/3/6.
//

#ifndef FUCK_PTSD_ANIMATION_H
#define FUCK_PTSD_ANIMATION_H

#include "MainCharacter.h"
#include "Animation.h"
#include "Util/Time.hpp"

namespace Animation {
glm::vec2 moveCameraByTime(unsigned long firstTimeMs,
                           unsigned long duringTimeMs, glm::vec2 destination,
                           glm::vec2 cameraPosition);
bool movePlayerByTime(unsigned long firstTimeMs, unsigned long duringTimeMs,
                      glm::vec2 destination,
                      std::shared_ptr<MainCharacter> player);
void movePlayerAnimation(unsigned long firstTimeMs, unsigned long duringTimeMs,
                         glm::vec2 move, std::shared_ptr<MainCharacter> player);
} // namespace Animation

#endif // FUCK_PTSD_ANIMATION_H
