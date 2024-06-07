#ifndef GREEN_SLIME_H
#define GREEN_SLIME_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class GreenSlime final : public Dungeon::Enemy {
public:
    GreenSlime(const s_Enemy& _Enemy, const std::shared_ptr<MapData> mapData);

    void Move() override;

private:
    const glm::vec2 m_FrameSize = {26, 26};
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // GREEN_SLIME_H
