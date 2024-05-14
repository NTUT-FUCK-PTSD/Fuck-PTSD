#ifndef FUCK_PTSD_2024_05_14_DRAGONGREEN_H
#define FUCK_PTSD_2024_05_14_DRAGONGREEN_H

#include <memory>
#include <random>
#include "Dungeon/Direction.h"
#include "Dungeon/Enemy.h"

namespace Dungeon::Enemies {
class DragonGreen final : public Dungeon::Enemy {
public:
    DragonGreen(
        const s_Enemy&                  u_Enemy,
        const std::shared_ptr<MapData>& mapData
    );

    void Move() override;

private:
    void UpdateProperties();

    const glm::vec2 m_FrameSize = {54, 51};

    bool m_Attack = false;
};
}  // namespace Dungeon::Enemies

#endif  // FUCK_PTSD_2024_05_14_DRAGONGREEN_H
