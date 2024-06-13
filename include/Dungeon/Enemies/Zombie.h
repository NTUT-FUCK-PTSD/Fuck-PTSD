#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <memory>
#include <random>
#include <stdexcept>

#include "Dungeon/Direction.h"
#include "Dungeon/Enemies/CSnake.h"
#include "Dungeon/Enemies/KingCongaBridge.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Zombie final : public Dungeon::Enemy {
public:
    Zombie(const s_Enemy& _Enemy, const std::shared_ptr<MapData> mapData);

    void Move() override;

    void Struck(const std::size_t damage) override;

    void UpdateFace();
    void SnakeVersion(const std::size_t priority, const bool direction);
    void SetSnakeHead();
    void SetPreviousSnake(const std::shared_ptr<CSnake> snake);
    void SetNextSnake(const std::shared_ptr<CSnake> snake);
    std::shared_ptr<CSnake> GetSnake() const { return m_Snake; }
    void SetBridge(const std::shared_ptr<KingCongaBridge> bridge) {
        m_Bridge = bridge;
    }

private:
    void UpdateProperties();

    const glm::vec2          m_FrameSize = {24, 25};
    std::vector<std::size_t> m_ZombieNormalFrames;
    std::vector<std::size_t> m_ZombieShadowFrames;
    std::vector<std::size_t> m_AttackFrames;
    std::vector<std::size_t> m_ShadowAttackFrames;
    std::vector<std::size_t> m_BackFrames;
    std::vector<std::size_t> m_ShadowBackFrames;

    bool m_Attack = false;

    std::size_t            m_Direction = 0;
    std::vector<glm::vec2> m_Movement = {TOP, RIGHT, BOTTOM, LEFT};

    std::random_device                         m_RandomDevice;
    std::mt19937                               m_RandomGenerator;
    std::uniform_int_distribution<std::size_t> m_Distribution;

    std::shared_ptr<CSnake> m_PreviousSnake = nullptr;
    std::shared_ptr<CSnake> m_NextSnake = nullptr;
    std::shared_ptr<CSnake> m_Snake = nullptr;
    // false means left, true means right
    bool m_SnakeDirection = false;

    std::shared_ptr<KingCongaBridge> m_Bridge = nullptr;
};

}  // namespace Enemies
}  // namespace Dungeon

#endif  // ZOMBIE_H
