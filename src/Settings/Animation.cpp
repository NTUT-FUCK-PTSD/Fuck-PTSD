//
// Created by adven on 2024/3/10.
//

#include "Animation.h"
#include "Dungeon/Elements.h"
#include "Util/Logger.hpp"

glm::vec2 Animation::moveCameraByTime(unsigned long firstTimeMs,
                                      unsigned long lastTimeMs,
                                      glm::vec2 destination,
                                      glm::vec2 cameraPosition) {
    unsigned long passTimeMs = Util::Time::GetElapsedTimeMs() - firstTimeMs;
    if (passTimeMs > lastTimeMs || cameraPosition == destination) {
        return destination;
    }
    float ratio = (float)passTimeMs / lastTimeMs;
    glm::vec2 current = cameraPosition;
    glm::vec2 move = destination - current;
    return current + move * ratio;
}

bool Animation::movePlayerByTime(unsigned long firstTimeMs,
                                 unsigned long lastTimeMs,
                                 glm::vec2 destination,
                                 std::shared_ptr<MainCharacter> player) {
    unsigned long passTimeMs = Util::Time::GetElapsedTimeMs() - firstTimeMs;
    if (passTimeMs > lastTimeMs || player->GetPosition() == destination) {
        player->SetPosition(destination);
        return true;
    }
    float ratio = (float)passTimeMs / lastTimeMs;
    glm::vec2 current = player->GetPosition();
    glm::vec2 move = destination - current;
    player->SetPosition(current + move * ratio);
    return false;
}

void Animation::movePlayerAnimation(unsigned long firstTimeMs,
                                    unsigned long lastTimeMs, glm::vec2 move,
                                    std::shared_ptr<MainCharacter> player) {
    unsigned long passTimeMs = Util::Time::GetElapsedTimeMs() - firstTimeMs;

    if (passTimeMs > lastTimeMs) {
        return;
    }
    glm::vec2 current = player->GetPosition();
    if (passTimeMs <= lastTimeMs / 2.0f) {
        float ratio = (float)passTimeMs / (lastTimeMs / 2);
        player->SetPosition(current + move * ratio);
    }
    else {
        unsigned long nPassTimeMs =
            Util::Time::GetElapsedTimeMs() - firstTimeMs + (lastTimeMs / 2);
        float ratio = (float)nPassTimeMs / (lastTimeMs / 2);
        player->SetPosition(current - move * (1.0f - ratio));
    }
    return;
}
