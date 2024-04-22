#include "Dungeon/Enemies/Zombie.h"

namespace Dungeon {
Enemies::Zombie::Zombie(
    const s_Enemy&                       u_Enemy,
    const std::shared_ptr<SimpleMapData> simpleMapData
)
    : Enemy(u_Enemy, simpleMapData),
      m_RandomGenerator(m_RandomDevice()) {
    m_Animation = std::make_unique<Animation>(
        ToolBoxs::GamePostoPos(GetGamePosition())
    );
    m_BackFrames = {0, 1, 2, 3, 4, 5, 6, 7};
    m_NormalFrames = {8, 9, 10, 11, 12, 13, 14, 15};
    m_AttackFrames = {16, 17, 18, 19, 20, 21, 22, 23};
    m_ShadowBackFrames = {24, 25, 26, 27, 28, 29, 30, 31};
    m_ShadowFrames = {32, 33, 34, 35, 36, 37, 38, 39};
    m_ShadowAttackFrames = {40, 41, 42, 43, 44, 45, 46, 47};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/zombie.png",
        m_FrameSize,
        m_NormalFrames,
        true,
        100,
        true,
        100
    );
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();
    m_Direction = m_Distribution(
        m_RandomGenerator,
        std::uniform_int_distribution<std::size_t>::param_type{0, 3}
    );

    SetHealth(2);  // 1 heart
    SetDamage(2);  // 1 heart
    SetCoin(1);
}
}  // namespace Dungeon

namespace Dungeon::Enemies {
void Zombie::Move() {
    m_WillMovePosition = m_GamePosition + m_Movement[m_Direction];

    if (IsVaildMove(m_WillMovePosition)) {
        if (m_WillMovePosition == GetPlayerPosition()) {
            AttackPlayer();
            m_Attack = !m_Attack;
            return;
        }
        m_CanMove = true;
    } else {
        switch (m_Direction) {
            case 0:
                m_Direction = 2;
                break;
            case 1:
                m_Direction = 3;
                break;
            case 2:
                m_Direction = 0;
                break;
            case 3:
                m_Direction = 1;
                break;
        }
        m_WillMovePosition = m_GamePosition + m_Movement[m_Direction];

        if (IsVaildMove(m_WillMovePosition) && m_Attack) {
            if (m_WillMovePosition == GetPlayerPosition()) {
                AttackPlayer();
                m_Attack = !m_Attack;
                return;
            }
            m_CanMove = true;
        } else {
            m_CanMove = false;
        }
    }
    if (!m_Attack) {
        m_WillMovePosition = m_GamePosition;
    }

    if (m_CanMove) {
        m_SimpleMapData->SetHasEntity(
            GamePostion2MapIndex(GetGamePosition()),
            false
        );
        m_SimpleMapData->SetHasEntity(
            m_SimpleMapData->GamePosition2MapIndex(m_WillMovePosition),
            true
        );
    }
    m_Attack = !m_Attack;
}
void Zombie::Update() {
    UpdateFace();
    if (m_Direction == 0) {
        m_SpriteSheet->SetFrames(
            GetShadow() ? m_ShadowBackFrames : m_BackFrames
        );
    } else if (m_Attack) {
        m_SpriteSheet->SetFrames(
            GetShadow() ? m_ShadowAttackFrames : m_AttackFrames
        );
    } else {
        m_SpriteSheet->SetFrames(GetShadow() ? m_ShadowFrames : m_NormalFrames);
    }

    // Collision
    if (m_CanMove && !m_Animation->IsAnimating()) {
        SetGamePosition(m_WillMovePosition);
        m_Animation->MoveByTime(
            200,
            ToolBoxs::GamePostoPos(m_WillMovePosition),
            m_Direction
        );
        m_CanMove = false;
    }
    m_Animation->UpdateAnimation(true);
    if (m_Animation->IsAnimating()) {
        m_Transform.translation = m_Animation->GetAnimationPosition();
    }
    SetZIndex(m_Animation->GetAnimationZIndex());
}

void Zombie::UpdateFace() {
    if (m_Direction == 0 || m_Direction == 3) {
        SetFace(true);
        return;
    }
    SetFace(false);
}
}  // namespace Dungeon::Enemies
