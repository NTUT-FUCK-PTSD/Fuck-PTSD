#ifndef GREEN_SLIME_H
#define GREEN_SLIME_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class GreenSlime : public Dungeon::Enemy {
public:
    GreenSlime(const s_Enemy &u_Enemy);

    void Move() override;

private:
    const glm::vec2 m_FrameSize = {26, 26};
};
} // namespace Enemies
} // namespace Dungeon

#endif // ENEMY_H
