#ifndef GHOST_H
#define GHOST_H

#include "Animation.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class Ghost final : public Dungeon::Enemy, private Animation {
public:
    Ghost(const s_Enemy &u_Enemy,
          const std::shared_ptr<SimpleMapData> &simpleMapData);

    void SetTransparent(bool transparent);

    glm::vec2 FindNextToPlayer() override;

    void Struck(const size_t &damage) override;

    void Move() override;

    void Update() override;

private:
    const glm::vec2 m_FrameSize = {24, 24};

    size_t m_LastDistance = 0;
    size_t m_Distance = 0;

    bool m_Transparent = false;
};
} // namespace Enemies
} // namespace Dungeon

#endif // GHOST_H
