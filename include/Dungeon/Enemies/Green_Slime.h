#ifndef GREEN_SLIME_H
#define GREEN_SLIME_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Green_Slime : public Dungeon::Enemy {
public:
    Green_Slime(const s_Enemy &u_Enemy);

    void Move() override;

private:
    const glm::vec2 m_FrameSize = {26, 26};
};
} // namespace Enemies
} // namespace Dungeon

#endif // ENEMY_H
