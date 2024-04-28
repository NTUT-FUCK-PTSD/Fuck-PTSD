#include "Dungeon/Enemies/Bat.h"

namespace Dungeon {
Enemies::Bat::Bat(
    const s_Enemy&                       u_Enemy,
    const std::shared_ptr<SimpleMapData> simpleMapData
)
    : Enemy(u_Enemy, simpleMapData),
      m_RandomGenerator(m_RandomDevice()) {
    m_NormalFrames = {0, 1, 2, 3};
    m_ShadowFrames = {4, 5, 6, 7};

    switch (u_Enemy.type) {
    case 6:
        m_SpriteSheet = std::make_shared<SpriteSheet>(
            ASSETS_DIR "/entities/bat.png",
            m_FrameSize,
            m_NormalFrames,
            true,
            100,
            true,
            100
        );
        SetHealth(2);  // 1 heart
        SetDamage(1);  // 0.5 heart
        SetCoin(2);
        break;
    case 7:
        m_SpriteSheet = std::make_shared<SpriteSheet>(
            ASSETS_DIR "/entities/bat_red.png",
            m_FrameSize,
            m_NormalFrames,
            true,
            100,
            true,
            100
        );
        SetHealth(2);  // 1 heart
        SetDamage(2);  // 1 heart
        SetCoin(3);
        m_Tick = 1;
        break;
    case 8:
        m_SpriteSheet = std::make_shared<SpriteSheet>(
            ASSETS_DIR "/entities/bat_green.png",
            m_FrameSize,
            m_NormalFrames,
            true,
            100,
            true,
            100
        );
        SetHealth(2);  // 1 heart
        SetDamage(3);  // 1.5 heart
        SetCoin(20);
        m_Tick = 1;
        break;
    }
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();
    m_AnimationType = 4;
}
}  // namespace Dungeon

namespace Dungeon::Enemies {
void Bat::Move() {
    if (m_State > m_Tick - 1) {
        m_State = 0;
    }
    if (m_State == m_Tick - 1) {
        for (std::size_t i = 0; i < 4; i++) {
            if (IsVaildMove(GetGamePosition() + m_Movement[i])) {
                m_RandomPool.push_back(i);
            }
        }
        RandomMove();
    }
    m_State++;
}

void Bat::RandomMove() {
    if (m_RandomPool.empty()) {
        return;
    }
    std::size_t index = 0;
    while (!m_RandomPool.empty()) {
        index = m_Distribution(
            m_RandomGenerator,
            std::uniform_int_distribution<std::size_t>::param_type{
              0,
              m_RandomPool.size() - 1
            }
        );
        switch (m_RandomPool[index]) {
        case 0:
            m_AnimationType = 0;
            m_WillMovePosition = GetGamePosition() + TOP;
            break;
        case 1:
            m_AnimationType = 1;
            m_WillMovePosition = GetGamePosition() + RIGHT;
            break;
        case 2:
            m_AnimationType = 2;
            m_WillMovePosition = GetGamePosition() + BOTTOM;
            break;
        case 3:
            m_AnimationType = 3;
            m_WillMovePosition = GetGamePosition() + LEFT;
            break;
        }
        if (IsVaildMove(m_WillMovePosition)) {
            UpdateFace();
            CanMove();
            return;
        }
        m_RandomPool.erase(m_RandomPool.begin() + index);
    }
}

void Bat::UpdateFace() {
    if (m_AnimationType == 1) {
        SetFace(true);
    } else if (m_AnimationType == 3) {
        SetFace(false);
    }
}

}  // namespace Dungeon::Enemies
