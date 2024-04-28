#ifndef GHOST_H
#define GHOST_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Ghost final : public Dungeon::Enemy {
public:
    Ghost(
        const s_Enemy&                       u_Enemy,
        const std::shared_ptr<SimpleMapData> simpleMapData
    );

    void SetTransparent(bool transparent);

    void Struck(const std::size_t damage) override;

    void Move() override;

    void AttackPlayer() override;

private:
    const glm::vec2 m_FrameSize = {24, 24};

    std::size_t m_LastDistance;

    bool m_Transparent = false;
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // GHOST_H
