#include "Dungeon/Enemies/Bat.h"

namespace Dungeon {
Enemies::Bat::Bat(const s_Enemy &u_Enemy,
                  const std::shared_ptr<SimpleMapData> &simpleMapData)
    : Enemy(u_Enemy, simpleMapData),
      Animation(ToolBoxs::GamePostoPos(GetGamePosition())),
      m_RandomGenerator(m_RandomDevice()) {
    m_NormalFrames = {0, 1, 2, 3};
    m_ShadowFrames = {4, 5, 6, 7};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/bat.png", m_FrameSize, m_NormalFrames, true, 100,
        true, 100);
    m_Drawable = m_SpriteSheet;
    m_WillMovePosition = GetGamePosition();

    SetHealth(2); // 1 heart
    SetDamage(1); // 0.5 heart
    SetCoin(2);
}
Enemies::Bat::Bat(const s_Enemy &u_Enemy,
                  const std::shared_ptr<SimpleMapData> &simpleMapData,
                  const std::string &filepath)
    : Enemy(u_Enemy, simpleMapData),
      Animation(ToolBoxs::GamePostoPos(GetGamePosition())),
      m_RandomGenerator(m_RandomDevice()) {
    m_NormalFrames = {0, 1, 2, 3};
    m_ShadowFrames = {4, 5, 6, 7};
    m_SpriteSheet = std::make_shared<SpriteSheet>(
        filepath, m_FrameSize, m_NormalFrames, true, 100, true, 100);
    m_Drawable = m_SpriteSheet;

    SetHealth(2); // 1 heart
    SetDamage(1); // 0.5 heart
    SetCoin(2);
}
} // namespace Dungeon

namespace Dungeon::Enemies {
void Bat::Move() {
    MoveBat();
}
void Bat::MoveBat() {
    if (m_IsAnimating) {
        m_AnimationPosition = m_AnimationDestination;
        Update();
    }
    m_NeedToMove = false;
    if (m_State > m_Tick - 1) {
        m_State = 0;
    }
    if (m_State == m_Tick - 1) {
        m_NeedToMove = true;
        m_RandomPool = {0, 1, 2, 3};
        RandomMove();
    }
    m_State++;
}
void Bat::Update() {
    // Collision
    if (m_CanMove && !m_IsAnimating) {
        MoveByTime(200, ToolBoxs::GamePostoPos(m_WillMovePosition));
        m_NeedToMove = false;
        m_CanMove = false;
    }
    // else if (!m_CanMove && m_NeedToMove) {
    //     RandomMove();
    // }

    // Update animation
    UpdateAnimation(false);
    if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
        m_Transform.translation = m_AnimationPosition;
    }

    // Update z index
    SetZIndex(m_AnimationZIndex);
}

void Bat::RandomMove() {
    if (m_RandomPool.empty()) {
        m_NeedToMove = false;
        return;
    }
    size_t index = 0;
    while (!m_RandomPool.empty()) {
        index =
            m_Distribution(m_RandomGenerator,
                           std::uniform_int_distribution<size_t>::param_type{
                               0, m_RandomPool.size() - 1});
        switch (m_RandomPool[index]) {
        case 0:
            m_WillMovePosition = GetGamePosition() + glm::vec2(0, 1);
            break;
        case 1:
            m_WillMovePosition = GetGamePosition() + glm::vec2(0, -1);
            break;
        case 2:
            m_WillMovePosition = GetGamePosition() + glm::vec2(1, 0);
            break;
        case 3:
            m_WillMovePosition = GetGamePosition() + glm::vec2(-1, 0);
            break;
        }
        if (IsVaildMove(m_WillMovePosition)) {
            m_CanMove = true;
            SetGamePosition(m_WillMovePosition);
            if (m_RandomPool[index] == 2) {
                SetFace(true);
            }
            else if (m_RandomPool[index] == 3) {
                SetFace(false);
            }
            return;
        }
        else {
            m_CanMove = false;
        }
        m_RandomPool.erase(m_RandomPool.begin() + index);
    }
}
} // namespace Dungeon::Enemies
