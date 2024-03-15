//
// Created by adven on 2024/3/10.
//

#include "Animation.h"
#include "Dungeon/Elements.h"

glm::vec2 Animation::moveCameraByTime(unsigned long firstTimeMs,
                                      unsigned long duringTimeMs,
                                      glm::vec2 destination,
                                      glm::vec2 cameraPosition) {
    unsigned long passTimeMs = Util::Time::GetElapsedTimeMs() - firstTimeMs;
    if (passTimeMs > duringTimeMs || cameraPosition == destination) {
        return destination;
    }
    float ratio = (float)passTimeMs / duringTimeMs;
    glm::vec2 current = cameraPosition;
    glm::vec2 move = destination - current;
    return current + move * ratio;
}

bool Animation::movePlayerByTime(unsigned long firstTimeMs,
                                 unsigned long duringTimeMs,
                                 glm::vec2 destination,
                                 std::shared_ptr<MainCharacter> player) {
    unsigned long passTimeMs = Util::Time::GetElapsedTimeMs() - firstTimeMs;
    if (passTimeMs > duringTimeMs || player->GetPosition() == destination) {
        player->SetPosition(destination);
        return true;
    }
    float ratio = (float)passTimeMs / duringTimeMs;
    glm::vec2 current = player->GetPosition();
    glm::vec2 move = destination - current;
    player->SetPosition(current + move * ratio);
    return false;
}

void Animation::movePlayerAnimation(unsigned long firstTimeMs,
                                    unsigned long duringTimeMs, glm::vec2 move,
                                    std::shared_ptr<MainCharacter> player) {
    unsigned long passTimeMs = Util::Time::GetElapsedTimeMs() - firstTimeMs;
    if (passTimeMs > duringTimeMs) {
        return;
    }
    glm::vec2 current = player->GetPosition();
    if (passTimeMs <= duringTimeMs / 2.0f) {
        float ratio = (float)passTimeMs / (duringTimeMs / 2);
        player->SetPosition(current + move * ratio);
    }
    else {
        float ratio =
            (float)(passTimeMs + (duringTimeMs / 2)) / (duringTimeMs / 2);
        player->SetPosition(current - move * (1.0f - ratio));
    }
    return;
}
