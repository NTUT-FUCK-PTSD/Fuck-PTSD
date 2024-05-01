#include "Dungeon/Enemy.h"

#include "Dungeon/AStar.h"
#include "Dungeon_config.h"
#include "ToolBoxs.h"

namespace Dungeon {

Enemy::Enemy(
    const s_Enemy&                       u_Enemy,
    const std::shared_ptr<SimpleMapData> simpleMapData
)
    : m_SimpleMapData(simpleMapData),
      m_GamePosition({u_Enemy.x, u_Enemy.y}),
      m_Animation(
          std::make_unique<Animation>(ToolBoxs::GamePostoPos(m_GamePosition))
      ),
      m_ID(u_Enemy.type),
      m_BeatDelay(u_Enemy.beatDelay),
      m_Lord(u_Enemy.lord == 1) {
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    SetGamePosition(m_GamePosition);
    m_Transform.translation = ToolBoxs::GamePostoPos(m_GamePosition);
    SetZIndex(m_Animation->GetAnimationZIndex());

    m_FullHeart = std::make_shared<Util::Image>(
        Dungeon::config::IMAGE_FULL_HEART_SM.data()
    );
    m_EmptyHeart = std::make_shared<Util::Image>(
        Dungeon::config::IMAGE_EMPTY_HEART_SM.data()
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
    m_SimpleMapData->SetHasEntity(
        m_SimpleMapData->GamePosition2MapIndex(m_GamePosition),
        false
    );
    m_SimpleMapData->SetHasEntity(
        m_SimpleMapData->GamePosition2MapIndex(gamePosition),
        true
    );
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
    if (GetVisible() == false || m_Seen == false) {
        return;
    }
    if (m_BeatDelay > 0) {
        m_BeatDelay--;
        return;
    }
    Move();
}

bool Enemy::IsVaildMove(const glm::vec2& position) {
    return m_SimpleMapData->IsPositionWalkable(position);
}

bool Enemy::DidAttack() {
    if (m_AttackPlayer) {
        m_AttackPlayer = false;
        return true;
    }
    return false;
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
        m_CanMove = false;
        m_WillMovePosition = GetGamePosition();
        m_AttackPlayer = true;
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

void Enemy::InitHealthBarImage(const glm::vec2 pixelPos) {
    const auto& hp = m_Health;

    float zindex = 0.01;
    for (std::size_t ii = 0; ii < hp; ii += 2) {
        const auto& obj = std::make_shared<Util::GameElement>();
        //        obj->SetDrawable(Dungeon::config::PTR_IMAGE_FULL_HEART_SM);
        obj->SetDrawable(m_FullHeart);
        obj->SetZIndex(99.0f + zindex);
        obj->SetPosition(pixelPos);
        obj->SetScale({DUNGEON_SCALE, DUNGEON_SCALE});

        AddChild(obj);
        LOG_INFO("test");
        m_HeartList.push_back(obj.get());

        zindex = zindex + 0.01;
    }
}

void Enemy::UpdateHeart(const glm::vec2& pixelPos) {
    glm::vec2 initOffsetPos = {0, 40};
    glm::vec2 eachOffsetPos = {-10, 0};

    if (m_HeartList.size() >= 2) {
        [&initOffsetPos, &eachOffsetPos, this]() {
            const auto heartNumber = m_HeartList.size();
            LOG_INFO(heartNumber);
            float x_width = static_cast<float>(
                heartNumber * 24 + (heartNumber - 1) * 2
            );
            initOffsetPos = glm::vec2{-(x_width / 2) + x_width / 6, 40};
            eachOffsetPos = glm::vec2{x_width / 3, 0};
        }();
    }

    auto pos = pixelPos + initOffsetPos;
    LOG_INFO(pos);
    for (const auto& elem : m_HeartList) {
        elem->SetPosition(pos);
        pos += eachOffsetPos;
    }
};

}  // namespace Dungeon
