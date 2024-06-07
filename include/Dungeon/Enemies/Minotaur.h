#ifndef MINOTAOUR_H
#define MINOTAOUR_H

#include "Enemy.h"

namespace Dungeon::Enemies {
enum class MinotaurState { Normal, Attack, Stunned, Stunned2 };
class Minotaur : public Enemy {
public:
    Minotaur(const s_Enemy& u_Enemy, const std::shared_ptr<MapData>& mapData);
    void Move() override;
    void AttackPlayer() override;
    void Struck(const std::size_t damage) override;

private:
    void ChangeStatus(MinotaurState state);
    void ChangeDirection(glm::vec2& direction);

    const glm::vec2          m_FrameSize = {50, 49};
    std::vector<std::size_t> m_NormalFrames_;
    std::vector<std::size_t> m_ShadowFrames_;
    std::vector<std::size_t> m_AttackFrames;
    std::vector<std::size_t> m_ShadowAttackFrames;
    std::vector<std::size_t> m_StunnedFrames;
    std::vector<std::size_t> m_ShadowStunnedFrames;

    bool          m_Attack;
    MinotaurState m_State;
    glm::vec2     m_Direction;
};
}  // namespace Dungeon::Enemies
#endif  // MINOTAOUR_H
