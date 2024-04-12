#ifndef BLUE_SLIME_H
#define BLUE_SLIME_H

#include "Animation.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class BlueSlime final : public Dungeon::Enemy, private Animation {
public:
    BlueSlime(const s_Enemy &u_Enemy,
              const std::shared_ptr<SimpleMapData> &simpleMapData);

    void Move() override;

    void Update() override;

private:
    const glm::vec2 m_FrameSize = {26, 25};

    size_t m_State = 0;
    bool m_NeedToMove = false;
    uint16_t m_AnimationType;
};
} // namespace Enemies
} // namespace Dungeon

#endif // BLUE_SLIME_H
