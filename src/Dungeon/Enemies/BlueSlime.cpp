#include "Dungeon/Enemies/BlueSlime.h"

namespace Dungeon {
Enemies::BlueSlime::BlueSlime(
    const s_Enemy &u_Enemy, const std::shared_ptr<SimpleMapData> simpleMapData)
    : Enemy(u_Enemy, simpleMapData),
      Animation(ToolBoxs::GamePostoPos(GetGamePosition())) {
    m_NormalFrames = {4, 5, 6, 7};
    m_ShadowFrames = {12, 13, 14, 15};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/slime_blue.png", m_FrameSize, m_NormalFrames,
        true, 100, true, 100);
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();

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
        m_AnimationType = 0;
    }
    else if (m_State == 3) {
        m_WillMovePosition = GetGamePosition() + glm::vec2(0, -1);
        m_NeedToMove = true;
        m_AnimationType = 2;
    }
    if (IsVaildMove(m_WillMovePosition)) {
        if (m_WillMovePosition == GetPlayerPosition()) {
            AttackPlayer();
            m_State++;
            return;
        }
        m_CanMove = true;
        m_SimpleMapData->SetHasEntity(GamePostion2MapIndex(GetGamePosition()),
                                      false);
        m_SimpleMapData->SetHasEntity(GamePostion2MapIndex(m_WillMovePosition),
                                      true);
    }
    else {
        m_CanMove = false;
        if (m_State == 2) {
            m_WillMovePosition = GetGamePosition() + glm::vec2(0, -1);
            m_State += 2;
            m_AnimationType = 2;
        }
        else if (m_State == 4) {
            m_WillMovePosition = GetGamePosition() + glm::vec2(0, 1);
            m_State = 2;
            m_AnimationType = 0;
        }
        m_NeedToMove = false;
    }

    m_State++;
}
void BlueSlime::Update() {
    if (m_CanMove && !m_IsAnimating) {
        SetGamePosition(m_WillMovePosition);
        MoveByTime(200, ToolBoxs::GamePostoPos(m_WillMovePosition),
                   m_AnimationType);
        m_NeedToMove = false;
        m_CanMove = false;
    }

    UpdateAnimation(true);
    if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
        m_Transform.translation = m_AnimationPosition;
    }
    SetZIndex(m_AnimationZIndex);
}

void BlueSlime::AttackPlayer() {
    if (GetPlayerPosition() == m_WillMovePosition) {
        m_NeedToMove = false;
        m_AnimationType = 0;
        Enemy::AttackPlayer();
    }
}
} // namespace Dungeon::Enemies
