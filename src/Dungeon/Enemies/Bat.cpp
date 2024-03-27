#include "Bat.h"
#include "ToolBoxs.h"

namespace Dungeon {
Enemies::Bat::Bat(const s_Enemy &u_Enemy,
                  const std::vector<std::shared_ptr<Tile>> &tiles,
                  const glm::vec2 &mapSize)
    : Enemy(u_Enemy, tiles, mapSize),
      m_RandomGenerator(m_RandomDevice()),
      m_Distribution(0, 1) {
    m_NormalFrames = {0, 1, 2, 3};
    m_ShadowFrames = {4, 5, 6, 7};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/bat.png", m_FrameSize, m_NormalFrames, true, 100,
        true, 100);
    m_Drawable = m_SpriteSheet;

    SetHealth(2); // 1 heart
    SetDamage(1); // 1.5 heart
    SetCoin(2);
    m_AnimationPosition = ToolBoxs::GamePostoPos(GetGamePosition());
}
} // namespace Dungeon

namespace Dungeon::Enemies {
void Bat::Move() {
    if (m_IsAnimating) {
        m_AnimationPosition = m_AnimationDestination;
        Update();
    }
    if (m_State > 1) {
        m_State = 0;
    }
    if (m_State == 1) {
        if (m_Distribution(m_RandomGenerator) == 1) {
            RandomMove(m_Direction, true);
        }
        else {
            RandomMove(m_Distribution(m_RandomGenerator) == 1, true);
        }
    }
    m_State++;
}
void Bat::Update() {
    UpdateAnimation();
    if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
        m_GamePosition = ToolBoxs::PosToGamePos(m_AnimationPosition);
        m_Transform.translation = m_AnimationPosition;
    }
    SetZIndex(ToolBoxs::PosToGamePos(m_Transform.translation).y + float(0.25));
}

void Bat::RandomMove(const bool &direction, const bool &isFirst) {
    if (direction) {
        if (IsVaildMove(GetGamePosition() + glm::vec2(0, 1)) &&
            m_Distribution(m_RandomGenerator) == 1) {
            MoveByTime(
                200,
                ToolBoxs::GamePostoPos(GetGamePosition() + glm::vec2(0, 1)), 0);
        }
        else if (IsVaildMove(GetGamePosition() + glm::vec2(0, -1))) {
            MoveByTime(
                200,
                ToolBoxs::GamePostoPos(GetGamePosition() + glm::vec2(0, -1)),
                2);
        }
        else {
            if (isFirst) {
                RandomMove(1, false);
            }
            return;
        }
        m_Direction = true;
    }
    else {
        if (IsVaildMove(GetGamePosition() + glm::vec2(-1, 0)) &&
            m_Distribution(m_RandomGenerator) == 1) {
            MoveByTime(
                200,
                ToolBoxs::GamePostoPos(GetGamePosition() + glm::vec2(-1, 0)),
                1);
        }
        else if (IsVaildMove(GetGamePosition() + glm::vec2(1, 0))) {
            MoveByTime(
                200,
                ToolBoxs::GamePostoPos(GetGamePosition() + glm::vec2(1, 0)), 3);
        }
        else {
            if (isFirst) {
                RandomMove(0, false);
            }
            return;
        }
        m_Direction = false;
    }
}
} // namespace Dungeon::Enemies
