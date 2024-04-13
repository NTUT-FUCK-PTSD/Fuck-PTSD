#ifndef BAT_H
#define BAT_H

#include <random>

#include "Animation.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Bat : public Dungeon::Enemy, private Animation {
public:
    Bat(const s_Enemy &u_Enemy,
        const std::shared_ptr<SimpleMapData> simpleMapData);
    virtual ~Bat() = default;

    void Move() override;

    void Update() override;

protected:
    Bat(const s_Enemy &u_Enemy,
        const std::shared_ptr<SimpleMapData> simpleMapData,
        const std::string &filepath);

    void MoveBat();
    std::size_t m_Tick = 2;

private:
    void RandomMove();
    const glm::vec2 m_FrameSize = {24, 24};
    std::size_t m_State = 0;

    bool m_NeedToMove = false;
    std::vector<std::size_t> m_RandomPool = {0, 1, 2, 3};

    std::random_device m_RandomDevice;
    std::mt19937 m_RandomGenerator;
    std::uniform_int_distribution<std::size_t> m_Distribution;
};
} // namespace Enemies
} // namespace Dungeon

#endif // BAT_H
