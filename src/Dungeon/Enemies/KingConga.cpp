#include "Dungeon/Enemies/KingConga.h"

#include "Dungeon/MapData.h"
#include "Settings/ToolBoxs.h"
#include "Util/Logger.hpp"

namespace Dungeon {
Enemies::KingConga::KingConga(
    const s_Enemy&                 _Enemy,
    const std::shared_ptr<MapData> mapData
)
    : Enemy(_Enemy, mapData) {
    m_NormalFramesRight = {0, 1, 4};
    m_NormalFramesLeft = {2, 3, 4};
    m_NormalFramesNone = {4};
    m_NormalFramesWalk = {5, 6};
    m_ShadowFramesRight = {7, 8, 11};
    m_ShadowFramesLeft = {9, 10, 11};
    m_ShadowFramesNone = {11};
    m_ShadowFramesWalk = {12, 13};
    m_NormalFrames = m_NormalFramesNone;
    m_ShadowFrames = m_ShadowFramesNone;
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/king_conga.png",
        m_FrameSize,
        m_NormalFrames,
        false,
        100,
        false,
        100
    );
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();

    InitHealth(4);  // 2 hearts
    SetDamage(4);   // 2 hearts
    SetCoin(0);
}
}  // namespace Dungeon
namespace Dungeon::Enemies {
void KingConga::Move() {
    LOG_INFO("Status: {}", static_cast<std::size_t>(m_State));
    if (m_Bridge->LeftSnake && m_Bridge->RightSnake) { SetState(State::WALK); }
    if (m_State == State::RIGHTSIT) {
        SetState(State::LEFTSIT);
    } else if (m_State == State::LEFTSIT) {
        SetState(State::RIGHTSIT);
    } else if (m_State == State::WALK) {
        if (m_Attack) {
            m_WillMovePosition = FindNextToPlayer(true);
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
        m_Attack = !m_Attack;
    }
    m_SpriteSheet->Play();
}

void KingConga::Struck(const std::size_t damage) {
    if (m_State == State::RIGHTSIT || m_State == State::LEFTSIT) { return; }
    Enemy::Struck(damage);
}

void KingConga::SetState(const State state) {
    m_State = state;
    switch (state) {
    case State::RIGHTSIT:
        m_NormalFrames = m_NormalFramesRight;
        m_ShadowFrames = m_ShadowFramesRight;
        break;
    case State::LEFTSIT:
        m_NormalFrames = m_NormalFramesLeft;
        m_ShadowFrames = m_ShadowFramesLeft;
        break;
    case State::WALK:
        m_NormalFrames = m_NormalFramesWalk;
        m_ShadowFrames = m_ShadowFramesWalk;
        break;
    }
    m_SpriteSheet->SetFrames(GetShadow() ? m_ShadowFrames : m_NormalFrames);
}

}  // namespace Dungeon::Enemies
