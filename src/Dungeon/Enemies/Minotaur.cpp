#include "Dungeon/Enemies/Minotaur.h"

#include "Dungeon/MapData.h"

namespace Dungeon::Enemies {
Minotaur::Minotaur(
    const s_Enemy&                  _Enemy,
    const std::shared_ptr<MapData>& mapData
)
    : Enemy(_Enemy, mapData) {
    m_NormalFrames_ = {0, 1, 2, 3};
    m_AttackFrames = {4};
    m_StunnedFrames = {5, 6, 7, 8};
    m_ShadowFrames_ = {9, 10, 11, 12};
    m_ShadowAttackFrames = {13};
    m_ShadowStunnedFrames = {14, 15, 16, 17};

    m_NormalFrames = m_NormalFrames_;
    m_ShadowFrames = m_ShadowFrames_;

    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/minotaur.png",
        m_FrameSize,
        m_NormalFrames,
        true,
        100,
        true,
        100
    );

    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();

    InitHealth(6);
    SetDamage(2);
    SetCoin(10);

    m_Attack = false;
    m_State = MinotaurState::Normal;
}

void Minotaur::ChangeStatus(MinotaurState state) {
    switch (state) {
    case MinotaurState::Normal: {
        m_NormalFrames = m_NormalFrames_;
        m_ShadowFrames = m_ShadowFrames_;
        break;
    }
    case MinotaurState::Attack: {
        m_NormalFrames = m_AttackFrames;
        m_ShadowFrames = m_ShadowAttackFrames;
        break;
    }
    case MinotaurState::Stunned: {
        m_NormalFrames = m_StunnedFrames;
        m_ShadowFrames = m_ShadowStunnedFrames;
        break;
    }
    case MinotaurState::Stunned2: {
        m_NormalFrames = m_StunnedFrames;
        m_ShadowFrames = m_ShadowStunnedFrames;
        break;
    }
    }
    m_SpriteSheet->SetFrames(GetShadow() ? m_ShadowFrames : m_NormalFrames);
    m_State = state;
}

void Minotaur::ChangeDirection(glm::vec2& direction) {
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
    m_Direction = direction;
}

void Minotaur::Move() {
    switch (m_State) {
    case MinotaurState::Normal: {
        auto direction = GetPlayerPosition() - GetGamePosition();
        if (direction.x == 0 && direction.y != 0) {
            ChangeStatus(MinotaurState::Attack);
            direction = {0, direction.y > 0 ? 1 : -1};
            ChangeDirection(direction);
        } else if (direction.x != 0 && direction.y == 0) {
            ChangeStatus(MinotaurState::Attack);
            direction = {direction.x > 0 ? 1 : -1, 0};
            ChangeDirection(direction);
        }

        m_WillMovePosition = FindNextToPlayer();
        direction = m_WillMovePosition - GetGamePosition();

        if (IsVaildMove(m_WillMovePosition)) {
            ChangeDirection(direction);
            CanMove();
        }
        break;
    }
    case MinotaurState::Attack: {
        m_WillMovePosition = GetGamePosition() + m_Direction;

        auto mapIndex = GamePostion2MapIndex(m_WillMovePosition);
        if (m_MapData->GetTile(mapIndex)->IsWall()) {
            Event::EventQueue.dispatch(this, WallRemoveEventArgs(mapIndex));
            ChangeStatus(MinotaurState::Stunned);
        }

        if (IsVaildMove(m_WillMovePosition)) {
            CanMove();
        } else {
            ChangeStatus(MinotaurState::Stunned);
            m_WillMovePosition = GetGamePosition();
        }
        break;
    }
    case MinotaurState::Stunned: {
        m_WillMovePosition = GetGamePosition();
        ChangeStatus(MinotaurState::Stunned2);
        break;
    }
    case MinotaurState::Stunned2: {
        ChangeStatus(MinotaurState::Normal);
        break;
    }
    }
}

void Minotaur::AttackPlayer() {
    if (m_State == MinotaurState::Attack) {
        Enemy::AttackPlayer();
        ChangeStatus(MinotaurState::Stunned);
    }
}

void Minotaur::Struck(const std::size_t damage) {
    Enemy::Struck(damage);
    if (m_Dead) { Event::EventQueue.dispatch(this, UnlockStairsEventArgs(0)); }
}

}  // namespace Dungeon::Enemies
