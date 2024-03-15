//
// Created by adven on 2024/3/6.
//

#ifndef FUCK_PTSD_ANIMATION_H
#define FUCK_PTSD_ANIMATION_H

#include <iostream>
#include <map>

#include "MainCharacter.h"
#include "Util/Time.hpp"

namespace Animation {

namespace MoveMode {
struct triangle {
    const std::map<std::size_t, glm::ivec2> DownAction = {
        {4, {0, -4}}, {8, {0, 6}}, {16, {0, -2}}};
    const std::map<std::size_t, glm::ivec2> UpAction = {
        {4, {0, 4}}, {8, {0, -6}}, {16, {0, 2}}};

    const std::map<std::size_t, glm::ivec2> LeftAction = {
        {4, {-2, 0}}, {8, {1, 4}}, {16, {1, -4}}};
    const std::map<std::size_t, glm::ivec2> RightAction = {
        {4, {2, 0}}, {8, {-1, 4}}, {16, {-1, -4}}};

    // vector's order is important here.
    // UP, RIGHT, DOWN, LEFT,
    const std::vector<std::map<std::size_t, glm::ivec2>> Actions = {
        UpAction, RightAction, DownAction, LeftAction};
};
} // namespace MoveMode

bool move_player(std::shared_ptr<std::int16_t> animationPass,
                 unsigned long firstTime, MainCharacter::Direction direction,
                 std::shared_ptr<MainCharacter> GameObject);
} // namespace Animation
#endif // FUCK_PTSD_ANIMATION_H
