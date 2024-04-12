#ifndef ORANGE_SLIME_H
#define ORANGE_SLIME_H

#include "Animation.h"
#include "Dungeon/Enemy.h"
#include <random>

namespace Dungeon {
namespace Enemies {
class OrangeSlime final : public Dungeon::Enemy, private Animation {
public:
    OrangeSlime(const s_Enemy &u_Enemy,
                const std::shared_ptr<SimpleMapData> &simpleMapData);

    void Move() override;

    void Update() override;

    void AttackPlayer() override;

private:
    const glm::vec2 m_FrameSize = {26, 26};

    size_t m_State = 0;
    bool m_NeedToMove = false;

    std::random_device m_RandomDevice;
    std::mt19937 m_RandomGenerator;
    std::uniform_int_distribution<size_t> m_Distribution;
    size_t m_StartIdx = 0;

    std::vector<glm::vec2> m_Movement = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};
} // namespace Enemies
} // namespace Dungeon

#endif // ORANGE_SLIME_H
