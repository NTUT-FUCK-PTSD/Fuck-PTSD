#ifndef WRAITH_H
#define WRAITH_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Wraith final : public Dungeon::Enemy {
public:
    Wraith(const s_Enemy& _Enemy, const std::shared_ptr<MapData> mapData);

    void Move() override;

private:
    const glm::vec2 m_FrameSize = {24, 24};
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // WRAITH_H
