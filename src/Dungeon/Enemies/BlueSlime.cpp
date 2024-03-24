#include "BlueSlime.h"

namespace Dungeon {
Enemies::BlueSlime::BlueSlime(const s_Enemy &u_Enemy)
    : Enemy(u_Enemy) {
    m_NormalFrames = {4, 5, 6, 7};
    m_ShadowFrames = {12, 13, 14, 15};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/slime_blue.png", m_FrameSize, m_NormalFrames,
        true, 100, true, 100);
    m_Drawable = m_SpriteSheet;

    SetHealth(2);
    SetDamage(50);
    SetCoin(1);
}
} // namespace Dungeon

namespace Dungeon::Enemies {
void BlueSlime::Move() {
    if (m_State > 3) {
        m_State = 0;
    }
    if (m_State == 1) {
        SetPosition(GetPosition() + glm::vec2(0, 1));
    }
    else if (m_State == 3) {
        SetPosition(GetPosition() + glm::vec2(0, -1));
    }
    m_State++;
}
} // namespace Dungeon::Enemies
