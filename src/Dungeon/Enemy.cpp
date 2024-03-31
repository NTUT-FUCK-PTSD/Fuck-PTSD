#include "Dungeon/Enemy.h"
#include "ToolBoxs.h"

namespace Dungeon {

Enemy::Enemy(const s_Enemy &u_Enemy,
             const std::shared_ptr<SimpleMapData> &simpleMapData)
    : m_SimpleMapData(simpleMapData),
      m_GamePosition({u_Enemy.x, u_Enemy.y}),
      m_BeatDelay(u_Enemy.beatDelay),
      m_Lord(u_Enemy.lord == 1) {
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    SetGamePosition(m_GamePosition);
}

void Enemy::SetShadow(const bool &shadow) {
    m_Shadow = shadow;
    m_SpriteSheet->SetFrames(shadow ? m_ShadowFrames : m_NormalFrames);
}

void Enemy::SetGamePosition(const glm::vec2 &gamePosition) {
    m_GamePosition = gamePosition;
    m_WillMovePosition = gamePosition;
    m_Transform.translation = ToolBoxs::GamePostoPos(gamePosition);
    SetZIndex(m_GamePosition.y + float(0.25));
}

void Enemy::SetLord(const bool &lord) {
    m_Lord = lord;
    if (m_Lord) {
        m_Transform.scale += m_Transform.scale;
        m_Damage += m_Damage;
        m_Health += m_Health;
        m_Coin = 24;
    }
}

void Enemy::TempoMove() {
    if (m_BeatDelay > 0) {
        m_BeatDelay--;
        return;
    }
    Move();
}

bool Enemy::IsVaildMove(const glm::vec2 &position) {
    return m_SimpleMapData->IsPositionWalkable(position);
}

} // namespace Dungeon
