//
// Created by adven on 2024/3/10.
//

#include "Animation.h"
#include "Dungeon/Elements.h"
#include "Util/Logger.hpp"

bool Animation::move_player(std::shared_ptr<std::int16_t> animationPass,
                            unsigned long firstTime,
                            MainCharacter::Direction direction,
                            std::shared_ptr<MainCharacter> player) {

    if (direction == MainCharacter::Direction::NONE) {
        return true;
    }

    movePlayerByTime(
        firstTime, 3000,
        {player->GetPosition().x,
         player->GetPosition().y + Dungeon::DUNGEON_TILE_WIDTH * 3},
        player);
    *animationPass = 0;
    return true;
}

glm::vec2 Animation::moveCameraByTime(unsigned long firstTimeMs,
                                      unsigned long lastTimeMs,
                                      glm::vec2 destination,
                                      glm::vec2 cameraPosition) {
    unsigned long passTime = Util::Time::GetElapsedTimeMs() - firstTimeMs;
    if (passTime > lastTimeMs || cameraPosition == destination) {
        return destination;
    }
    float ratio = (float)passTime / lastTimeMs;
    glm::vec2 current = cameraPosition;
    glm::vec2 move = destination - current;
    return current + move * ratio;
}

bool Animation::movePlayerByTime(unsigned long firstTimeMs,
                                 unsigned long lastTimeMs,
                                 glm::vec2 destination,
                                 std::shared_ptr<MainCharacter> player) {
    unsigned long passTime = Util::Time::GetElapsedTimeMs() - firstTimeMs;
    if (passTime > lastTimeMs || player->GetPosition() == destination) {
        player->SetPosition(destination);
        return true;
    }
    float ratio = (float)passTime / lastTimeMs;
    glm::vec2 current = player->GetPosition();
    glm::vec2 move = destination - current;
    player->SetPosition(current + move * ratio);
    return false;
}
