#include "Dungeon/Enemies/Monkey.h"

#include "Dungeon/MapData.h"

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
        InitHealth(4);  // 2 heart
        SetDamage(0);   // 0 heart
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
        InitHealth(4);  // 2 heart
        SetDamage(0);   // 0 heart
        SetCoin(3);
        break;
    }
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();
    m_MonkeyNormalFrames = m_NormalFrames;
    m_MonkeyShadowFrames = m_ShadowFrames;
}

void Monkey::Move() {}
}  // namespace Dungeon::Enemies
