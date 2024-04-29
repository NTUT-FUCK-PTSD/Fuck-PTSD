#ifndef GREEN_SLIME_H
#define GREEN_SLIME_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class GreenSlime final : public Dungeon::Enemy {
public:
    GreenSlime(
        const s_Enemy&                       u_Enemy,
        const std::shared_ptr<SimpleMapData> simpleMapData
    );

    void Move() override;

    void Update() override;

private:
    const glm::vec2 m_FrameSize = {26, 26};
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // GREEN_SLIME_H
