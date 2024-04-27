#ifndef ORANGE_SLIME_H
#define ORANGE_SLIME_H

#include <random>

#include "Dungeon/Direction.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class OrangeSlime final : public Dungeon::Enemy {
public:
    OrangeSlime(
        const s_Enemy&                       u_Enemy,
        const std::shared_ptr<SimpleMapData> simpleMapData
    );

    void Move() override;

    void Update() override;

    void UpdateState();

private:
    void UpdateFace(const glm::vec2& direction);

    const glm::vec2 m_FrameSize = {26, 26};

    std::size_t m_State = 0;

    std::random_device                         m_RandomDevice;
    std::mt19937                               m_RandomGenerator;
    std::uniform_int_distribution<std::size_t> m_Distribution;
    std::size_t                                m_StartIdx = 0;

    std::vector<glm::vec2> m_Movement = {BOTTOM, RIGHT, TOP, LEFT};
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // ORANGE_SLIME_H
