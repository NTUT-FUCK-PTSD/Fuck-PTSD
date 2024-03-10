//
// Created by adven on 2024/3/6.
//

#ifndef FUCK_PTSD_ANIMATION_H
#define FUCK_PTSD_ANIMATION_H

#include <iostream>
#include <map>

#include "MainCharacter.h"

namespace Animation {

namespace MoveMode {
struct triangle {
    std::size_t totalFrames = 15;

    const std::map<std::size_t, glm::vec2> UpAction = {
        {4, {0, -4}}, {10, {0, 6}}, {14, {0, -2}}};
    const std::map<std::size_t, glm::vec2> DownAction = {
        {4, {0, 4}}, {10, {0, -6}}, {14, {0, 2}}};

    const std::map<std::size_t, glm::vec2> RightAction = {
        {4, {-2, 0}}, {10, {1, 4}}, {14, {1, -6}}};
    const std::map<std::size_t, glm::vec2> LeftAction = {
        {4, {2, 0}}, {10, {-1, 4}}, {14, {-1, -6}}};

    // vector's order is important here.
    // UP, RIGHT, DOWN, LEFT,
    const std::vector<std::map<std::size_t, glm::vec2>> Actions = {
        UpAction, RightAction, DownAction, LeftAction};
};
} // namespace MoveMode

bool move_player(
    std::size_t current_frame, std::size_t firstFrame,
    MainCharacter::Direction direction,
    //                 std::shared_ptr<Animation::MoveMode::triangle>
    //                 animation_mode,
    std::shared_ptr<MainCharacter> GameObject);
} // namespace Animation
#endif // FUCK_PTSD_ANIMATION_H
