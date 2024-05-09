#ifndef MONKEY_H
#define MONKEY_H

#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Monkey final : public Dungeon::Enemy {
public:
    Monkey(const s_Enemy& u_Enemy, const std::shared_ptr<MapData> mapData);

    void Move() override;

private:
    const glm::vec2          m_FrameSize = {25, 24};
    std::vector<std::size_t> m_BackFrames;
    std::vector<std::size_t> m_ShadowBackFrames;
    std::vector<std::size_t> m_MonkeyNormalFrames;
    std::vector<std::size_t> m_MonkeyShadowFrames;
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // MONKEY_H
