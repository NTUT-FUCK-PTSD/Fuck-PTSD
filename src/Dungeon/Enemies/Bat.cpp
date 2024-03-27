#include "Bat.h"
#include "ToolBoxs.h"

namespace Dungeon {
Enemies::Bat::Bat(const s_Enemy &u_Enemy)
    : Enemy(u_Enemy),
      Animation(ToolBoxs::GamePostoPos(GetGamePosition())),
      m_RandomGenerator(m_RandomDevice()) {
    m_NormalFrames = {0, 1, 2, 3};
    m_ShadowFrames = {4, 5, 6, 7};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/bat.png", m_FrameSize, m_NormalFrames, true, 100,
        true, 100);
    m_Drawable = m_SpriteSheet;

    SetHealth(2); // 1 heart
    SetDamage(1); // 1.5 heart
    SetCoin(2);
}
} // namespace Dungeon

namespace Dungeon::Enemies {
void Bat::Move() {
    if (m_IsAnimating) {
        m_AnimationPosition = m_AnimationDestination;
        Update();
    }
    m_NeedToMove = false;
    if (m_State > 1) {
        m_State = 0;
    }
    if (m_State == 1) {
        m_NeedToMove = true;
        m_RandomPool = {0, 1, 2, 3};
        RandomMove();
    }
    m_State++;
}
void Bat::Update() {
    // Collision
    if (m_CanMove && !m_IsAnimating) {
        MoveByTime(200, ToolBoxs::GamePostoPos(m_WillMovePosition));
        m_GamePosition = m_WillMovePosition;
        m_NeedToMove = false;
    }
    else if (!m_CanMove && m_NeedToMove) {
        RandomMove();
    }

    // Update animation
    UpdateAnimation(false);
    if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
        m_Transform.translation = m_AnimationPosition;
    }

    // Update z index
    SetZIndex(m_AnimationZIndex);
}

void Bat::RandomMove() {
    if (m_RandomPool.empty()) {
        m_NeedToMove = false;
        return;
    }
    size_t index = m_Distribution(
        m_RandomGenerator, std::uniform_int_distribution<size_t>::param_type{
                               0, m_RandomPool.size() - 1});
    switch (m_RandomPool[index]) {
    case 0:
        m_WillMovePosition = GetGamePosition() + glm::vec2(0, 1);
        m_RandomPool.erase(
            std::remove(m_RandomPool.begin(), m_RandomPool.end(), 0),
            m_RandomPool.end());
        return;
    case 1:
        m_WillMovePosition = GetGamePosition() + glm::vec2(0, -1);
        m_RandomPool.erase(
            std::remove(m_RandomPool.begin(), m_RandomPool.end(), 1),
            m_RandomPool.end());
        return;
    case 2:
        m_WillMovePosition = GetGamePosition() + glm::vec2(-1, 0);
        m_RandomPool.erase(
            std::remove(m_RandomPool.begin(), m_RandomPool.end(), 2),
            m_RandomPool.end());
        return;
    case 3:
        m_WillMovePosition = GetGamePosition() + glm::vec2(1, 0);
        m_RandomPool.erase(
            std::remove(m_RandomPool.begin(), m_RandomPool.end(), 3),
            m_RandomPool.end());
        return;
    }
}
} // namespace Dungeon::Enemies
