
#include "Dungeon/Enemies/DragonGreen.h"
#include <memory>
#include "Dungeon/MapData.h"
#include "SpriteSheet.hpp"

namespace Dungeon::Enemies {
DragonGreen::DragonGreen(
    const s_Enemy&                  u_Enemy,
    const std::shared_ptr<MapData>& mapData
)
    : Enemy(u_Enemy, mapData) {
    m_NormalFrames = {0, 1};
    m_ShadowFrames = {2, 3};

    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/dragon_green.png",
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
    SetDamage(1);
    SetCoin(2);

    m_Attack = false;
}
void DragonGreen::Move() {
    if (m_Attack) {
        m_WillMovePosition = FindNextToPlayer();
        auto direction = m_WillMovePosition - GetGamePosition();

        if (IsVaildMove(m_WillMovePosition)) {
            // Set Animation
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
            CanMove();
        }
    }
    m_Attack = !m_Attack;
}

void DragonGreen::Struck(const std::size_t damage) {
    Enemy::Struck(damage);
    if (m_Dead) { Event::EventQueue.dispatch(this, UnlockStairsEventArgs(0)); }
}

}  // namespace Dungeon::Enemies
