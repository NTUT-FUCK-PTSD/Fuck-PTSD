// #include "BlueSlime.h"
// #include "ToolBoxs.h"
// namespace Dungeon {
// Enemies::BlueSlime::BlueSlime(const s_Enemy &u_Enemy)
//     : Enemy(u_Enemy) {
//     m_NormalFrames = {4, 5, 6, 7};
//     m_ShadowFrames = {12, 13, 14, 15};
//     m_SpriteSheet = std::make_shared<SpriteSheet>(
//         ASSETS_DIR "/entities/slime_blue.png", m_FrameSize, m_NormalFrames,
//         true, 100, true, 100);
//     m_Drawable = m_SpriteSheet;

//     SetHealth(4); // 2 hearts
//     SetDamage(2); // 1 heart
//     SetCoin(2);
//     m_AnimationPosition = ToolBoxs::GamePostoPos(GetGamePosition());
// }
// } // namespace Dungeon

// namespace Dungeon::Enemies {
// void BlueSlime::Move() {
//     if (m_IsAnimating) {
//         m_AnimationPosition = m_AnimationDestination;
//         Update();
//     }
//     if (m_State > 3) {
//         m_State = 0;
//     }
//     if (m_State == 1) {
//         MoveByTime(200,
//                    ToolBoxs::GamePostoPos(GetGamePosition() + glm::vec2(0,
//                    1)), 0);
//     }
//     else if (m_State == 3) {
//         MoveByTime(200,
//                    ToolBoxs::GamePostoPos(GetGamePosition() + glm::vec2(0,
//                    -1)), 2);
//     }
//     m_State++;
// }
// void BlueSlime::Update() {
//     UpdateAnimation();
//     if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
//         m_GamePosition = ToolBoxs::PosToGamePos(m_AnimationPosition);
//         m_Transform.translation = m_AnimationPosition;
//     }
//     SetZIndex(ToolBoxs::PosToGamePos(m_Transform.translation).y +
//     float(0.25));
// }
// } // namespace Dungeon::Enemies
