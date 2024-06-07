#ifndef SKELETON_H
#define SKELETON_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Skeleton final : public Dungeon::Enemy {
public:
    Skeleton(const s_Enemy& _Enemy, const std::shared_ptr<MapData> mapData);

    void Move() override;

private:
    void UpdateProperties();

    const glm::vec2          m_FrameSize = {24, 28};
    std::vector<std::size_t> m_SkeletonNormalFrames;
    std::vector<std::size_t> m_SkeletonShadowFrames;
    std::vector<std::size_t> m_AttackFrames;
    std::vector<std::size_t> m_ShadowAttackFrames;

    bool m_Attack = false;
    bool m_CanDropHead = false;
    // bool m_DropHead = false;
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // SKELETON_H
