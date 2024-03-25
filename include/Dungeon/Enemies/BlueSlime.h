#ifndef BLUE_SLIME_H
#define BLUE_SLIME_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class BlueSlime : public Dungeon::Enemy {
public:
    BlueSlime(const s_Enemy &u_Enemy);

    void Move() override;

private:
    const glm::vec2 m_FrameSize = {26, 25};

    size_t m_State = 0;
};
} // namespace Enemies
} // namespace Dungeon

#endif // ENEMY_H