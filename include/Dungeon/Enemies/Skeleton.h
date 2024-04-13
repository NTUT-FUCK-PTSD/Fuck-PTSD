#ifndef SKELETON_H
#define SKELETON_H

#include "Animation.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Skeleton final : public Dungeon::Enemy, private Animation {
public:
    Skeleton(const s_Enemy &u_Enemy,
             const std::shared_ptr<SimpleMapData> simpleMapData);

    void Move() override;

    void Update() override;

    void AttackPlayer() override;

private:
    const glm::vec2 m_FrameSize = {24, 28};
    std::vector<std::size_t> m_AttackFrames;
    std::vector<std::size_t> m_ShadowAttackFrames;

    bool m_Attack = false;
    bool m_CanDropHead = false;
    bool m_DropHead = false;
    uint16_t m_AnimationType;
};
} // namespace Enemies
} // namespace Dungeon

#endif // SKELETON_H
