#include "Dungeon/Enemies/BlueSlime.h"

#include "Dungeon/MapData.h"

namespace Dungeon {
Enemies::BlueSlime::BlueSlime(
    const s_Enemy&                 u_Enemy,
    const std::shared_ptr<MapData> mapData
)
    : Enemy(u_Enemy, mapData) {
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

    InitHealth(4);  // 2 hearts
    SetDamage(2);   // 1 heart
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
        CanMove();
    }
    m_State++;
}
}  // namespace Dungeon::Enemies
