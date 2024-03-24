#include "Green_Slime.h"

namespace Dungeon {
Enemies::Green_Slime::Green_Slime(const s_Enemy &u_Enemy)
    : Enemy(u_Enemy) {
    m_NormalFrames = {0, 1, 2, 3};
    m_ShadowFrames = {4, 5, 6, 7};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/slime_green.png", m_FrameSize, m_NormalFrames,
        true, 100, true, 100);
    m_Drawable = m_SpriteSheet;

    SetHealth(2);
    SetDamage(50);
    SetCoin(1);
}
} // namespace Dungeon

namespace Dungeon::Enemies {
void Green_Slime::Move() {} // Green_Slime does not move
} // namespace Dungeon::Enemies
