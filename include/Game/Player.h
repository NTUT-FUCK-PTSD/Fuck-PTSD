//
// Created by 陳世昂 on 2024/4/27.
//

#ifndef FUCK_PTSD_PLAYER_H
#define FUCK_PTSD_PLAYER_H

#include "Util/GameObject.hpp"

namespace Game {
class Player final : public Util::GameObject {
public:
    enum Direction { UP = 0, RIGHT, DOWN, LEFT, NONE };

    explicit Player() = default;
    ~Player() override = default;

    [[nodiscard]]
    glm::vec2 GetGamePos() const;

    [[nodiscard]]

    private:
};
}  // namespace Game

#endif  // FUCK_PTSD_PLAYER_H
