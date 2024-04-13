#include "Dungeon/Enemies/Skeleton.h"

namespace Dungeon {
Enemies::Skeleton::Skeleton(const s_Enemy &u_Enemy,
                            const std::shared_ptr<SimpleMapData> simpleMapData)
    : Enemy(u_Enemy, simpleMapData),
      Animation(ToolBoxs::GamePostoPos(GetGamePosition())) {
    if (u_Enemy.type == 3) {
        m_NormalFrames = {0, 1, 2, 3};
        m_AttackFrames = {4, 5, 6, 7};
        m_ShadowFrames = {16, 17, 18, 19};
        m_ShadowAttackFrames = {20, 21, 22, 23};

        m_SpriteSheet = std::make_shared<SpriteSheet>(
            ASSETS_DIR "/entities/skeleton.png", m_FrameSize, m_NormalFrames,
            true, 100, true, 100);
        SetHealth(2); // 1 heart
        SetDamage(1); // 0.5 heart
        SetCoin(2);
        m_CanDropHead = false;
    }
    else if (u_Enemy.type == 4) {
        m_NormalFrames = {0, 1, 2, 3};
        m_AttackFrames = {4, 5, 6, 7};
        m_ShadowFrames = {17, 18, 19, 20};
        m_ShadowAttackFrames = {21, 22, 23, 24};
        m_SpriteSheet = std::make_shared<SpriteSheet>(
            ASSETS_DIR "/entities/skeleton_yellow.png", m_FrameSize,
            m_ShadowFrames, true, 100, true, 100);
        SetHealth(4); // 2 hearts
        SetDamage(3); // 1.5 hearts
        SetCoin(2);
        m_CanDropHead = true;
    }
    else if (u_Enemy.type == 5) {
        m_NormalFrames = {0, 1, 2, 3};
        m_AttackFrames = {4, 5, 6, 7};
        m_ShadowFrames = {17, 18, 19, 20};
        m_ShadowAttackFrames = {21, 22, 23, 24};
        m_SpriteSheet = std::make_shared<SpriteSheet>(
            ASSETS_DIR "/entities/skeleton_black.png", m_FrameSize,
            m_ShadowFrames, true, 100, true, 100);
        SetHealth(6); // 3 hearts
        SetDamage(4); // 2 hearts
        SetCoin(4);
        m_CanDropHead = true;
    }

    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();

    m_Attack = false;
}
} // namespace Dungeon

namespace Dungeon::Enemies {
void Skeleton::Move() {
    if (m_Attack) {
        m_WillMovePosition = FindNextToPlayer();
        auto direction = m_WillMovePosition - GetGamePosition();

        if (IsVaildMove(m_WillMovePosition)) {
            if (m_WillMovePosition == GetPlayerPosition()) {
                m_CanMove = false;
                m_WillMovePosition = GetGamePosition();
                m_AnimationType = 0;
                m_AttackPlayer = true;
                m_Attack = !m_Attack;
                return;
            }
            m_CanMove = true;
            m_SimpleMapData->SetHasEntity(
                GamePostion2MapIndex(GetGamePosition()), false);
            m_SimpleMapData->SetHasEntity(
                GamePostion2MapIndex(m_WillMovePosition), true);
            if (direction.x > 0) {
                SetFace(false);
                m_AnimationType = 1;
            }
            else if (direction.x < 0) {
                SetFace(true);
                m_AnimationType = 3;
            }
            else if (direction.y > 0) {
                m_AnimationType = 0;
            }
            else if (direction.y < 0) {
                m_AnimationType = 2;
            }
        }
        else {
            m_CanMove = false;
        }
    }
    m_Attack = !m_Attack;
}
void Skeleton::Update() {
    if (m_Attack) {
        m_SpriteSheet->SetFrames(GetShadow() ? m_ShadowAttackFrames
                                             : m_AttackFrames);
    }
    else {
        m_SpriteSheet->SetFrames(GetShadow() ? m_ShadowFrames : m_NormalFrames);
    }

    // Collision
    if (m_CanMove && !m_IsAnimating) {
        SetGamePosition(m_WillMovePosition);
        MoveByTime(200, ToolBoxs::GamePostoPos(m_WillMovePosition),
                   m_AnimationType);
        m_CanMove = false;
    }
    UpdateAnimation(true);
    if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
        m_Transform.translation = m_AnimationPosition;
    }
    SetZIndex(m_AnimationZIndex);
}
} // namespace Dungeon::Enemies
