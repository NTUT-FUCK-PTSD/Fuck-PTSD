#include "Dungeon/Enemies/RedBat.h"

namespace Dungeon {
Enemies::RedBat::RedBat(const s_Enemy &u_Enemy)
    : Bat(u_Enemy, ASSETS_DIR "/entities/bat_red.png") {

    SetHealth(2); // 1 heart
    SetDamage(1); // 1 heart
    SetCoin(3);
    m_Tick = 1;
}
} // namespace Dungeon
