#ifndef FUCK_PTSD_2024_05_12_SHOPKEEPER_H
#define FUCK_PTSD_2024_05_12_SHOPKEEPER_H

#include "Enemy.h"

namespace Dungeon::Enemies {
class Shopkeeper final : public Dungeon::Enemy {
public:
    Shopkeeper(const s_Enemy& u_Enemy, const std::shared_ptr<MapData>& mapData);

    void Move() override;

private:
    const glm::vec2 m_FrameSize = {47, 38};
};
}  // namespace Dungeon::Enemies

#endif  // FUCK_PTSD_2024_05_12_SHOPKEEPER_H
