#include "Dungeon/Enemies/Monkey.h"

#include "Dungeon/MapData.h"
#include "Enemy.h"
#include "Event/Event.h"
#include "Event/EventArgs.h"

namespace Dungeon::Enemies {
Monkey::Monkey(const s_Enemy& u_Enemy, const std::shared_ptr<MapData> mapData)
    : Enemy(u_Enemy, mapData) {
    m_NormalFrames = {0, 1, 2, 3};
    m_BackFrames = {4, 5};
    m_ShadowFrames = {6, 7, 8, 9};
    m_ShadowBackFrames = {10, 11};
    switch (u_Enemy.type) {
    case 9:
        m_SpriteSheet = std::make_shared<SpriteSheet>(
            ASSETS_DIR "/entities/monkey.png",
            m_FrameSize,
            m_NormalFrames,
            true,
            100,
            true,
            100
        );
        InitHealth(2);        // 1 heart
        m_HealthGrapple = 8;  // 4 hearts
        SetDamage(0);         // 0 heart
        SetCoin(1);
        break;
    case 10:
        m_SpriteSheet = std::make_shared<SpriteSheet>(
            ASSETS_DIR "/entities/monkey_white.png",
            m_FrameSize,
            m_NormalFrames,
            true,
            100,
            true,
            100
        );
        InitHealth(4);         // 2 hearts
        m_HealthGrapple = 12;  // 6 hearts
        SetDamage(0);          // 0 heart
        SetCoin(3);
        break;
    }
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();
    m_KnockbackAble = true;
}

void Monkey::Move() {
    if (m_Back) {
        OnPlayer();
        return;
    }
    m_WillMovePosition = FindNextToPlayer();
    auto direction = m_WillMovePosition - GetGamePosition();
    UpdateAnimationType(direction);
    UpdateProperties(direction);
    if (!m_Back) {
        CanMove();
    }
}

void Monkey::UpdateProperties(const glm::vec2& direction) {
    if (direction.x > 0) {
        SetFace(false);
    } else if (direction.x < 0) {
        SetFace(true);
    }
    m_SpriteSheet->SetFrames(GetShadow() ? m_ShadowFrames : m_NormalFrames);
}

void Monkey::AttackPlayer() {
    if (GetPlayerPosition() == m_WillMovePosition) {
        Event::EventQueue.dispatch(this, AttackPlayerEventArgs(GetDamage()));
        Event::SetAttackPlayer(false);
        if (!m_Back) {
            m_Back = true;
            m_SpriteSheet->SetFrames(
                GetShadow() ? m_ShadowBackFrames : m_BackFrames
            );
            auto deltaHealth = GetMaxHealth() - GetHealth();
            InitHealth(m_HealthGrapple);
            ChangeHealthBar(GetHealth() - deltaHealth);

            m_KnockbackAble = false;
            OnPlayer();
        }
    }
}

void Monkey::Update() {
    Enemy::Update();
    if (m_Dead) {
        return;
    }
    if (m_Back && !m_Animation->IsAnimating()) {
        auto player = m_MapData->GetPlayer();
        m_Transform.translation = player->GetTranslation();
        SetZIndex(player->GetZIndex() + 0.3125f);
    }
}

void Monkey::OnPlayer() {
    if (GetGamePosition() != GetPlayerPosition()) {
        Event::EventQueue.dispatch(
            this,
            EnemyMoveEventArgs(GamePostion2MapIndex(GetPlayerPosition()))
        );
    }
}
}  // namespace Dungeon::Enemies
