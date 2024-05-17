#ifndef FUCK_PTSD_2024_05_14_DRAGONGREEN_H
#define FUCK_PTSD_2024_05_14_DRAGONGREEN_H

#include <memory>
#include "Dungeon/Enemy.h"

namespace Dungeon::Enemies {
class DragonGreen final : public Dungeon::Enemy {
public:
    DragonGreen(
        const s_Enemy&                  u_Enemy,
        const std::shared_ptr<MapData>& mapData
    );

    void Move() override;

    bool IsBoss() const override { return true; }

private:
    const glm::vec2 m_FrameSize = {54, 51};

    bool m_Attack = false;
};
}  // namespace Dungeon::Enemies

#endif  // FUCK_PTSD_2024_05_14_DRAGONGREEN_H
