#include "Dungeon/Enemies/Zombie.h"
#include "MapData.h"

namespace Dungeon {
Enemies::Zombie::Zombie(
    const s_Enemy&                 _Enemy,
    const std::shared_ptr<MapData> mapData
)
    : Enemy(_Enemy, mapData),
      m_RandomGenerator(m_RandomDevice()) {
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

    m_ZombieNormalFrames = m_NormalFrames;
    m_ZombieShadowFrames = m_ShadowFrames;

    InitHealth(2);  // 1 heart
    SetDamage(2);   // 1 heart
    SetCoin(1);
}
}  // namespace Dungeon

namespace Dungeon::Enemies {
void Zombie::Move() {
    m_Attack = !m_Attack;
    if (m_Attack) {
        m_WillMovePosition = GetGamePosition() + m_Movement[m_Direction];

        if (IsVaildMove(m_WillMovePosition)) {
            CanMove();
        } else {
            switch (m_Direction) {
            case 0: m_Direction = 2; break;
            case 1: m_Direction = 3; break;
            case 2: m_Direction = 0; break;
            case 3: m_Direction = 1; break;
            }
            m_WillMovePosition = GetGamePosition() + m_Movement[m_Direction];

            if (IsVaildMove(m_WillMovePosition)) { CanMove(); }
        }
    }

    m_AnimationType = m_Direction;
    UpdateProperties();
}

void Zombie::UpdateFace() {
    if (m_Direction == 0 || m_Direction == 3) {
        SetFace(true);
        return;
    }
    SetFace(false);
}

void Zombie::UpdateProperties() {
    UpdateFace();
    if (m_Direction == 2) {
        m_NormalFrames = m_BackFrames;
        m_ShadowFrames = m_ShadowBackFrames;
    } else if (m_Attack) {
        m_NormalFrames = m_AttackFrames;
        m_ShadowFrames = m_ShadowAttackFrames;
    } else {
        m_NormalFrames = m_ZombieNormalFrames;
        m_ShadowFrames = m_ZombieShadowFrames;
    }
    m_SpriteSheet->SetFrames(GetShadow() ? m_ShadowFrames : m_NormalFrames);
}
}  // namespace Dungeon::Enemies
