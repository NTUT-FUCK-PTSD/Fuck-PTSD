#ifndef GHOST_H
#define GHOST_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Ghost final : public Dungeon::Enemy {
public:
    Ghost(const s_Enemy& _Enemy, const std::shared_ptr<MapData> mapData);

    void SetTransparent(bool transparent);

    void Struck(const std::size_t damage) override;

    void Move() override;

    void AttackPlayer() override;

private:
    const glm::vec2 m_FrameSize = {24, 24};

    bool m_Transparent = false;
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // GHOST_H
