#ifndef MONKEY_H
#define MONKEY_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Monkey final : public Dungeon::Enemy {
public:
    Monkey(const s_Enemy& _Enemy, const std::shared_ptr<MapData> mapData);

    void Move() override;

    void AttackPlayer() override;

    void UpdateProperties(const glm::vec2& direction);

    void Update() override;

private:
    void                     OnPlayer();
    const glm::vec2          m_FrameSize = {25, 24};
    std::vector<std::size_t> m_BackFrames;
    std::vector<std::size_t> m_ShadowBackFrames;
    std::size_t              m_HealthGrapple;

    bool m_Back = false;
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // MONKEY_H
