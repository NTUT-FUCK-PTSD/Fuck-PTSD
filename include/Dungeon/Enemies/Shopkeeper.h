#ifndef FUCK_PTSD_2024_05_12_SHOPKEEPER_H
#define FUCK_PTSD_2024_05_12_SHOPKEEPER_H

#include <memory>
#include <random>
#include "Dungeon/Direction.h"
#include "Elements.h"
#include "Enemy.h"
namespace Dungeon::Enemies {
class Shopkeeper final : public Dungeon::Enemy {
public:
    Shopkeeper(const s_Enemy& u_Enemy, const std::shared_ptr<MapData>& mapData);

    void Move() override;

    void Update() override;

private:
    void UpdateFace(const glm::vec2& direction);

    const glm::vec2 m_FrameSize = {47, 38};

    std::random_device                         m_RandomDevice;
    std::mt19937                               m_RandomGenerator;
    std::uniform_int_distribution<std::size_t> m_Distribution;
    std::size_t                                m_StartIdx = 0;

    std::vector<glm::vec2> m_Movement = {BOTTOM, RIGHT, TOP, LEFT};
};
}  // namespace Dungeon::Enemies

#endif  // FUCK_PTSD_2024_05_12_SHOPKEEPER_H
