#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <random>

#include "Animation.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Zombie final : public Dungeon::Enemy {
public:
    Zombie(
        const s_Enemy&                       u_Enemy,
        const std::shared_ptr<SimpleMapData> simpleMapData
    );

    void Move() override;

    void Update() override;

    void UpdateFace();

private:
    const glm::vec2          m_FrameSize = {24, 25};
    std::vector<std::size_t> m_AttackFrames;
    std::vector<std::size_t> m_ShadowAttackFrames;
    std::vector<std::size_t> m_BackFrames;
    std::vector<std::size_t> m_ShadowBackFrames;

    bool                   m_Attack = false;
    std::size_t            m_Direction = 0;
    std::vector<glm::vec2> m_Movement = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    std::random_device                         m_RandomDevice;
    std::mt19937                               m_RandomGenerator;
    std::uniform_int_distribution<std::size_t> m_Distribution;
    std::unique_ptr<Animation>                 m_Animation;
};

}  // namespace Enemies
}  // namespace Dungeon

#endif  // ZOMBIE_H
