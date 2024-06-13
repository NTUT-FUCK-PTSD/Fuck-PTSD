#ifndef KING_CONGA_H
#define KING_CONGA_H

#include <memory>

#include "Dungeon/Enemies/KingCongaBridge.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
namespace Enemies {
class KingConga final : public Dungeon::Enemy {
public:
    enum class State { RIGHTSIT, LEFTSIT, WALK };

    KingConga(const s_Enemy& _Enemy, const std::shared_ptr<MapData> mapData);

    void Move() override;

    void Struck(const std::size_t damage) override;

    void SetState(const State state);

    std::shared_ptr<KingCongaBridge> GetBridge() const { return m_Bridge; }

    bool IsBoss() const override { return true; }

private:
    const glm::vec2 m_FrameSize = {58, 79};

    std::vector<std::size_t> m_NormalFramesRight;
    std::vector<std::size_t> m_ShadowFramesRight;
    std::vector<std::size_t> m_NormalFramesLeft;
    std::vector<std::size_t> m_ShadowFramesLeft;
    std::vector<std::size_t> m_NormalFramesNone;
    std::vector<std::size_t> m_ShadowFramesNone;
    std::vector<std::size_t> m_NormalFramesWalk;
    std::vector<std::size_t> m_ShadowFramesWalk;

    State                            m_State = State::RIGHTSIT;
    std::shared_ptr<KingCongaBridge> m_Bridge =
        std::make_shared<KingCongaBridge>();
    bool m_Attack = false;
};
}  // namespace Enemies
}  // namespace Dungeon

#endif  // KING_CONGA_H
