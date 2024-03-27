#ifndef BLUE_SLIME_H
#define BLUE_SLIME_H

#include "Animation.h"
#include "Dungeon/Enemy.h"
#include <random>

namespace Dungeon {
namespace Enemies {
class Bat : public Dungeon::Enemy, public Animation {
public:
    Bat(const s_Enemy &u_Enemy, const std::vector<std::shared_ptr<Tile>> &tiles,
        const glm::vec2 &mapSize);

    void Move() override;

    void Update() override;

private:
    void RandomMove(const bool &direction, const bool &isFirst = false);
    const glm::vec2 m_FrameSize = {24, 24};
    size_t m_State = 0;
    bool m_Direction = false;

    std::random_device m_RandomDevice;
    std::mt19937 m_RandomGenerator;
    std::uniform_int_distribution<> m_Distribution;
};
} // namespace Enemies
} // namespace Dungeon

#endif // ENEMY_H
