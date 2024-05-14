#ifndef FUCK_PTSD_2024_05_14_DRAGONGREEN_H
#define FUCK_PTSD_2024_05_14_DRAGONGREEN_H

#include <memory>
#include <random>
#include "Dungeon/Direction.h"
#include "Dungeon/Enemy.h"

namespace Dungeon::Enemies {
class DragonGreen final : public Dungeon::Enemy {
public:
    DragonGreen(
        const s_Enemy&                  u_Enemy,
        const std::shared_ptr<MapData>& mapData
    );

    void Move() override;

    bool IsBoss() const override { return true; }

private:
    void UpdateProperties();

    const glm::vec2 m_FrameSize = {54, 51};

    std::vector<std::size_t> m_SkeletonNormalFrames;
    std::vector<std::size_t> m_SkeletonShadowFrames;
    std::vector<std::size_t> m_AttackFrames;
    std::vector<std::size_t> m_ShadowAttackFrames;

    bool m_Attack = false;
    bool m_CanDropHead = false;

    // std::vector<glm::vec2> m_Movement = {BOTTOM, RIGHT, TOP, LEFT};
};
}  // namespace Dungeon::Enemies

#endif  // FUCK_PTSD_2024_05_14_DRAGONGREEN_H
