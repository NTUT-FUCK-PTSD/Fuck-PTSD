
#ifndef FUCK_PTSD_HPMA_H
#define FUCK_PTSD_HPMA_H

/* Handle-Player-Movement-Action*/

#include "Dungeon/Map.h"
#include "Player.h"

namespace Game::Systems {
class HPMA final {
public:
    HPMA(Dungeon::Map* dungeonMap);

    void Dispatch(
        const std::string& weaponType,
        Player::Direction  dire,
        const std::string& imagePath
    );

private:
    Dungeon::Map* m_dungeonMap;
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HPMA_H
