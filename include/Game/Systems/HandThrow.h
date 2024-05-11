
#ifndef FUCK_PTSD_HANDTHROW_H
#define FUCK_PTSD_HANDTHROW_H

#include "Dungeon/Map.h"
#include "Player.h"

namespace Game::Systems {
class HandThrow final {
public:
    HandThrow(Dungeon::Map* dungeonMap);

    void Dispatch(
        const std::string& weaponType,
        Player::Direction  dire,
        const std::string& imagePath
    );

private:
    struct DP {
        Player::Direction dire;
        std::string       imagePath;
    };

    void Dagger(DP dp);
    void Spear(DP dp);

    Dungeon::Map* m_dungeonMap;
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HANDTHROW_H
