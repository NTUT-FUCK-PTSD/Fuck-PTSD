#include "Dungeon/Enemy.h"
#include "ToolBoxs.h"

namespace Dungeon {

Enemy::Enemy(const s_Enemy &u_Enemy)
    : m_Position({u_Enemy.x, u_Enemy.y}),
      m_BeatDelay(u_Enemy.beatDelay),
      m_Lord(u_Enemy.lord == 1) {
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    SetPosition(m_Position);
    SetZIndex(m_Position.y + float(0.25));
}

void Enemy::SetShadow(bool shadow) {
    m_Shadow = shadow;
    m_SpriteSheet->SetFrames(shadow ? m_ShadowFrames : m_NormalFrames);
}

void Enemy::SetPosition(const glm::vec2 &position) {
    m_Position = position;
    m_Transform.translation = {
        -m_Position.x * DUNGEON_TILE_WIDTH * DUNGEON_SCALE,
        -m_Position.y * DUNGEON_TILE_WIDTH * DUNGEON_SCALE};
}

void Enemy::SetLord(bool lord) {
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
    SetZIndex(m_Position.y + float(0.25));
    Move();
}

} // namespace Dungeon
