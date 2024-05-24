#ifndef BAT_H
#define BAT_H

#include <random>

#include "Dungeon/Direction.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Bat final : public Dungeon::Enemy {
public:
    Bat(const s_Enemy& u_Enemy, const std::shared_ptr<MapData> mapData);

    bool IsBoss() const override { return m_IsBoss; }

    void Move() override;

    void UpdateFace();

private:
    void        RandomMove();
    void        MoveBat();
    std::size_t m_Tick = 2;

private:
    bool        m_IsBoss = false;
    glm::vec2   m_FrameSize = {24, 24};
    std::size_t m_State = 0;

    std::vector<std::size_t> m_RandomPool = {};
    std::vector<glm::vec2>   m_Movement = {TOP, RIGHT, BOTTOM, LEFT};

    std::random_device                         m_RandomDevice;
    std::mt19937                               m_RandomGenerator;
    std::uniform_int_distribution<std::size_t> m_Distribution;
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // BAT_H
