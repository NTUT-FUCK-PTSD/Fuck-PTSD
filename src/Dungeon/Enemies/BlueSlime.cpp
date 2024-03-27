#include "Dungeon/Enemies/BlueSlime.h"
#include "ToolBoxs.h"
namespace Dungeon {
Enemies::BlueSlime::BlueSlime(const s_Enemy &u_Enemy)
    : Enemy(u_Enemy),
      Animation(ToolBoxs::GamePostoPos(GetGamePosition())) {
    m_NormalFrames = {4, 5, 6, 7};
    m_ShadowFrames = {12, 13, 14, 15};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/slime_blue.png", m_FrameSize, m_NormalFrames,
        true, 100, true, 100);
    m_Drawable = m_SpriteSheet;

    SetHealth(4); // 2 hearts
    SetDamage(2); // 1 heart
    SetCoin(2);
}
} // namespace Dungeon

namespace Dungeon::Enemies {
void BlueSlime::Move() {
    if (m_IsAnimating) {
        m_AnimationPosition = m_AnimationDestination;
        Update();
    }
    m_NeedToMove = false;
    if (m_State > 3) {
        m_State = 0;
    }
    if (m_State == 1) {
        m_WillMovePosition = GetGamePosition() + glm::vec2(0, 1);
        m_NeedToMove = true;
    }
    else if (m_State == 3) {
        m_WillMovePosition = GetGamePosition() + glm::vec2(0, -1);
        m_NeedToMove = true;
    }
    m_State++;
}
void BlueSlime::Update() {
    if (m_CanMove && !m_IsAnimating) {
        MoveByTime(200, ToolBoxs::GamePostoPos(m_WillMovePosition), 0);
        m_GamePosition = m_WillMovePosition;
        m_NeedToMove = false;
    }
    else if (!m_CanMove && m_NeedToMove) {
        if (m_State == 2) {
            m_WillMovePosition = GetGamePosition() + glm::vec2(0, -1);
            m_State += 2;
        }
        else if (m_State == 4) {
            m_WillMovePosition = GetGamePosition() + glm::vec2(0, 1);
            m_State = 2;
        }
        m_NeedToMove = false;
    }

    UpdateAnimation(true);
    if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
        m_Transform.translation = m_AnimationPosition;
    }
    SetZIndex(m_AnimationZIndex);
}
} // namespace Dungeon::Enemies
