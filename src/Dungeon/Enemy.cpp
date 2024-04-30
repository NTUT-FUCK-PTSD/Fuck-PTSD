#include "Dungeon/Enemy.h"

#include "Dungeon/AStar.h"
#include "Settings/ToolBoxs.h"

namespace Dungeon {

Enemy::Enemy(
    const s_Enemy&                       u_Enemy,
    const std::shared_ptr<SimpleMapData> simpleMapData
)
    : m_SimpleMapData(simpleMapData),
      m_Animation(
          std::make_unique<Animation>(ToolBoxs::GamePostoPos(m_GamePosition))
      ),
      m_GamePosition({u_Enemy.x, u_Enemy.y}),
      m_ID(u_Enemy.type),
      m_BeatDelay(u_Enemy.beatDelay),
      m_Lord(u_Enemy.lord == 1) {
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    SetGamePosition(m_GamePosition);
    m_Transform.translation = m_Animation->GetAnimationPosition();
    SetZIndex(m_Animation->GetAnimationZIndex());
    m_DrawableUpdate = MapEvent::Dispatcher.appendListener(
        EventType::DrawableUpdate,
        [this](const Event&) { Update(); }
    );
}

Enemy::~Enemy() {
    MapEvent::Dispatcher.removeListener(
        EventType::DrawableUpdate,
        m_DrawableUpdate
    );
}

void Enemy::SetShadow(const bool shadow) {
    if (!m_Seen) {
        if (!shadow) {
            m_Seen = !shadow;
        } else {
            m_Visible = false;
            return;
        }
    }
    if (m_Shadow == shadow) {
        return;
    }
    m_Shadow = shadow;
    m_SpriteSheet->SetFrames(shadow ? m_ShadowFrames : m_NormalFrames);
}

void Enemy::SetGamePosition(const glm::vec2& gamePosition) {
    m_GamePosition = gamePosition;
    m_WillMovePosition = gamePosition;
    // drawable would be updated depending on the enemy derived class
    // m_Transform.translation = ToolBoxs::GamePostoPos(gamePosition);
    // SetZIndex(m_GamePosition.y + float(0.25));
}

void Enemy::SetLord(const bool lord) {
    m_Lord = lord;
    if (m_Lord) {
        m_Transform.scale += m_Transform.scale;
        m_Damage += m_Damage;
        m_Health += m_Health;
        m_Coin = 24;
    }
}

void Enemy::TempoMove() {
    // if (GetVisible() == false || m_Seen == false) {
    //     return;
    // }
    if (m_BeatDelay > 0) {
        m_BeatDelay--;
        return;
    }
    Move();
}

bool Enemy::IsVaildMove(const glm::vec2& position) {
    return m_SimpleMapData->IsPositionWalkable(position);
}

glm::vec2 Enemy::FindNextToPlayer() {
    if (GetPlayerPosition() == GetGamePosition()) {
        return GetGamePosition();
    }
    auto path = Dungeon::AStar::FindPath(
        GetGamePosition(),
        GetPlayerPosition(),
        m_SimpleMapData,
        10
    );
    if (path.empty()) {
        return GetGamePosition();
    } else {
        return path[1];
    }
}

void Enemy::AttackPlayer() {
    if (GetPlayerPosition() == m_WillMovePosition) {
        MapEvent::Dispatcher.dispatch(
            EventType::AttackPlayer,
            Event{.type = EventType::AttackPlayer, .damage = GetDamage()}
        );
        m_WillMovePosition = GetGamePosition();
        m_Animation->MoveByTime(
            200,
            ToolBoxs::GamePostoPos(GetGamePosition()),
            m_AnimationType + 5
        );
    }
}

void Enemy::UpdateAnimationType(const glm::vec2& direction) {
    if (direction.x > 0) {
        m_AnimationType = 1;
    } else if (direction.x < 0) {
        m_AnimationType = 3;
    } else if (direction.y > 0) {
        m_AnimationType = 0;
    } else if (direction.y < 0) {
        m_AnimationType = 2;
    }
}

void Enemy::SetCameraUpdate(bool cameraUpdate) {
    SetVisible(cameraUpdate);
    for (auto& child : m_Children) {
        child->SetVisible(cameraUpdate);
    }
}

void Enemy::Update() {
    // Update animation
    m_Animation->UpdateAnimation(true);
    if (m_Animation->IsAnimating()) {
        m_Transform.translation = m_Animation->GetAnimationPosition();
    }

    // Update z index
    SetZIndex(m_Animation->GetAnimationZIndex());
}

void Enemy::CanMove() {
    if (m_WillMovePosition == GetPlayerPosition()) {
        AttackPlayer();
        return;
    }
    if (!m_Animation->IsAnimating()) {
        MapEvent::Dispatcher.dispatch(
            EventType::EnemyMove,
            Event{
              .type = EventType::EnemyMove,
              .from = GamePostion2MapIndex(m_GamePosition),
              .to = GamePostion2MapIndex(m_WillMovePosition)
            }
        );
        SetGamePosition(m_WillMovePosition);
        m_Animation->MoveByTime(
            200,
            ToolBoxs::GamePostoPos(m_WillMovePosition),
            m_AnimationType
        );
    }
}
}  // namespace Dungeon
