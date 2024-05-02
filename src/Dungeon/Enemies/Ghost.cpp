#include "Dungeon/Enemies/Ghost.h"

#include "Dungeon/AStar.h"
#include "Settings/ToolBoxs.h"

namespace Dungeon {
Enemies::Ghost::Ghost(
    const s_Enemy&                       u_Enemy,
    const std::shared_ptr<SimpleMapData> simpleMapData
)
    : Enemy(u_Enemy, simpleMapData) {
    m_NormalFrames = {0, 1};
    m_ShadowFrames = {2, 3};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/ghost.png",
        m_FrameSize,
        m_NormalFrames,
        true,
        100,
        true,
        100
    );
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();

    SetHealth(2);  // 1 heart
    SetDamage(1);  // 0.5 heart
    SetCoin(2);

    m_LastDistance =
        Dungeon::AStar::Heuristic(GetGamePosition(), GetPlayerPosition());

    this->InitHealthBarImage(ToolBoxs::GamePostoPos(GetGamePosition()));
}
}  // namespace Dungeon

namespace Dungeon::Enemies {
void Ghost::SetTransparent(bool transparent) {
    if (m_Transparent == transparent) {
        return;
    }
    m_Transparent = transparent;
    if (m_Transparent) {
        m_SpriteSheet->SetAlpha(128);
    } else {
        m_SpriteSheet->SetAlpha(255);
    }
}
void Ghost::Struck(const std::size_t damage) {
    if (m_Transparent) {
        return;
    }
    Enemy::Struck(damage);
}
void Ghost::Move() {
    auto tmp =
        Dungeon::AStar::Heuristic(GetGamePosition(), GetPlayerPosition());
    if (m_LastDistance > tmp || (m_Transparent && m_LastDistance == tmp)) {
        SetTransparent(true);
    } else {
        if (m_Transparent) {
            SetTransparent(false);
            return;
        }
    }
    m_LastDistance = tmp;

    if (!m_Transparent) {
        m_WillMovePosition = FindNextToPlayer();
        auto direction = m_WillMovePosition - GetGamePosition();

        if (IsVaildMove(m_WillMovePosition)) {
            if (direction.x > 0) {
                SetFace(false);
                m_AnimationType = 1;
            } else if (direction.x < 0) {
                SetFace(true);
                m_AnimationType = 3;
            } else if (direction.y > 0) {
                m_AnimationType = 0;
            } else if (direction.y < 0) {
                m_AnimationType = 2;
            }

            if (m_WillMovePosition == GetPlayerPosition()) {
                AttackPlayer();
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
            tmp -= 1;
        } else {
            m_CanMove = false;
        }
    }
}
void Ghost::Update() {
    // Collision
    if (m_CanMove && !m_Animation->IsAnimating()) {
        SetGamePosition(m_WillMovePosition);
        m_Animation
            ->MoveByTime(200, ToolBoxs::GamePostoPos(m_WillMovePosition), 4);
        m_CanMove = false;
    }
    m_Animation->UpdateAnimation(true);
    if (m_Animation->IsAnimating()) {
        m_Transform.translation = m_Animation->GetAnimationPosition();
    }
    SetZIndex(m_Animation->GetAnimationZIndex());

    UpdateHeart(m_Transform.translation);
}

void Ghost::AttackPlayer() {
    if (m_Transparent) {
        m_WillMovePosition = GetGamePosition();
        return;
    }
    Enemy::AttackPlayer();
}
}  // namespace Dungeon::Enemies
