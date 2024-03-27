#ifndef BLUE_SLIME_H
#define BLUE_SLIME_H

#include "Animation.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class BlueSlime : public Dungeon::Enemy, public Animation {
public:
    BlueSlime(const s_Enemy &u_Enemy);

    void Move() override;

    void Update() override;

private:
    const glm::vec2 m_FrameSize = {26, 25};

    size_t m_State = 0;
    bool m_NeedToMove = false;
};
} // namespace Enemies
} // namespace Dungeon

#endif // BLUE_SLIME_H
