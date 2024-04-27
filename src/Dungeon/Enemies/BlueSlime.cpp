#include "Dungeon/Enemies/BlueSlime.h"

#include "Settings/ToolBoxs.h"

namespace Dungeon {
Enemies::BlueSlime::BlueSlime(
    const s_Enemy&                       u_Enemy,
    const std::shared_ptr<SimpleMapData> simpleMapData
)
    : Enemy(u_Enemy, simpleMapData) {
    m_NormalFrames = {4, 5, 6, 7};
    m_ShadowFrames = {12, 13, 14, 15};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/slime_blue.png",
        m_FrameSize,
        m_NormalFrames,
        true,
        100,
        true,
        100
    );
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();
    m_InitPosition = GetGamePosition();

    SetHealth(4);  // 2 hearts
    SetDamage(2);  // 1 heart
    SetCoin(2);

    if (!IsVaildMove(m_InitPosition + m_Move)) {
        m_Move = -m_Move;
    }
}
}  // namespace Dungeon

namespace Dungeon::Enemies {
void BlueSlime::Move() {
    if (m_State > 3) {
        m_State = 0;
    }
    if (m_State == 1) {
        if (GetGamePosition() == m_InitPosition) {
            m_WillMovePosition = m_InitPosition + m_Move;
        } else {
            m_WillMovePosition = m_InitPosition;
        }
    } else if (m_State == 3) {
        if (GetGamePosition() == m_InitPosition) {
            m_WillMovePosition = m_InitPosition + m_Move;
        } else {
            m_WillMovePosition = m_InitPosition;
        }
    }
    if (IsVaildMove(m_WillMovePosition)) {
        auto direction = m_WillMovePosition - GetGamePosition();
        UpdateAnimationType(direction);
        if (m_WillMovePosition == GetPlayerPosition()) {
            AttackPlayer();
            m_State++;
            return;
        }
        m_CanMove = true;
        m_SimpleMapData->SetHasEntity(
            GamePostion2MapIndex(GetGamePosition()),
            false
        );
        m_SimpleMapData->SetHasEntity(
            GamePostion2MapIndex(m_WillMovePosition),
            true
        );
    }
    m_State++;
}

void BlueSlime::Update() {
    if (m_CanMove && !m_Animation->IsAnimating()) {
        SetGamePosition(m_WillMovePosition);
        m_Animation->MoveByTime(
            200,
            ToolBoxs::GamePostoPos(m_WillMovePosition),
            m_AnimationType
        );
        m_CanMove = false;
    }

    m_Animation->UpdateAnimation(true);
    if (m_Animation->IsAnimating()) {
        m_Transform.translation = m_Animation->GetAnimationPosition();
    }
    SetZIndex(m_Animation->GetAnimationZIndex());
}
}  // namespace Dungeon::Enemies
