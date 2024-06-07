#include "Shopkeeper.h"

#include "ToolBoxs.h"

namespace Dungeon::Enemies {
Shopkeeper::Shopkeeper(
    const s_Enemy&                  _Enemy,
    const std::shared_ptr<MapData>& mapData
)
    : Enemy(_Enemy, mapData) {
    m_NormalFrames = {0, 1, 2, 3, 4, 5, 6, 7};
    m_ShadowFrames = {8, 9, 10, 11, 12, 13, 14, 15};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/shopkeeper.png",
        m_FrameSize,
        m_NormalFrames,
        true,
        100,
        true,
        100
    );
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();

    InitHealth(18);
    SetDamage(100);
    SetCoin(8);
}

void Shopkeeper::Move() {
    m_UnnecssaryAnimation = true;
    m_Animation->MoveByTime(200, ToolBoxs::GamePostoPos(GetGamePosition()), 4);
}
}  // namespace Dungeon::Enemies
