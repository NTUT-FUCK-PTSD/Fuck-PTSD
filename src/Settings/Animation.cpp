//
// Created by adven on 2024/3/10.
//

#include "Animation.h"

bool Animation::move_player(std::size_t current_frame, std::size_t firstFrame,
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

    // count how many frame from start to now.
    // the frame count the number cross 60 to 1.
    const std::size_t count_frames = (firstFrame > 45 && current_frame < 15)
                                         ? current_frame + (60 - firstFrame)
                                         : current_frame - firstFrame;

    for (auto action : animation_mode->Actions[direction]) {

        if (count_frames <= action.first) {
            GameObject->move_player(action.second);
            //            MoveGameObject();
            return false;
        }
    }

    return true;
}
