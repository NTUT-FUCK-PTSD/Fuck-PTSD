//
// Created by adven on 2024/3/10.
//

#include "Animation.h"
#include "Util/Logger.hpp"

bool Animation::move_player(std::shared_ptr<std::int16_t> animationPass,
                            unsigned long firstTime,
                            MainCharacter::Direction direction,
                            std::shared_ptr<MainCharacter> GameObject) {

    if (direction == MainCharacter::Direction::NONE) {
        return true;
    }

    //    auto animation_mode =
    //    std::make_shared<Animation::MoveMode::triangle>();
    auto animation_mode = std::make_shared<Animation::MoveMode::triangle>();
    // outside
    // TODO: record firstframe

    for (auto action : animation_mode->Actions[direction]) {

        if (!(*animationPass & action.first) &&
            (Util::Time::GetElapsedTimeMs() - firstTime) /
                    (Util::Time::GetDeltaTime() * 1000.0f) <=
                action.first) {
            *animationPass |= action.first;
            GameObject->move_player(action.second);
            LOG_CRITICAL(action.first);
            //            MoveGameObject();

            return false;
        }
    }

    *animationPass = 0;
    return true;
}
