#include "Dungeon/Enemies/Wraith.h"

#include "Dungeon/MapData.h"

namespace Dungeon {
Enemies::Wraith::Wraith(
    const s_Enemy&                 _Enemy,
    const std::shared_ptr<MapData> mapData
)
    : Enemy(_Enemy, mapData) {
    m_NormalFrames = {0, 1, 2};
    m_ShadowFrames = {3, 4, 5};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/wraith.png",
        m_FrameSize,
        m_NormalFrames,
        true,
        100,
        true,
        100
    );
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();

    InitHealth(2);  // 1 heart
    SetDamage(1);   // 0.5 heart
    SetCoin(2);

    m_AnimationType = 4;
}
}  // namespace Dungeon

namespace Dungeon::Enemies {
void Wraith::Move() {
    m_WillMovePosition = FindNextToPlayer();
    auto direction = m_WillMovePosition - GetGamePosition();

    if (IsVaildMove(m_WillMovePosition)) {
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
}  // namespace Dungeon::Enemies
