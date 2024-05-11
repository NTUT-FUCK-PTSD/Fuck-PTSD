//
// Created by 陳世昂 on 2024/4/30.
//

#ifndef FUCK_PTSD_HPIS_H
#define FUCK_PTSD_HPIS_H

#include "Dungeon/Map.h"
#include "Game/Warehouse/Dagger.h"
#include "Player.h"
#include "Player_config.h"
#include "Util/Logger.hpp"
#include "Warehouse/Throw.h"

/**
 * @note This is "Handle Player-Interactive System"
 *
 */
namespace Game::Systems {
class ISC;

class HPIS final {
public:
    // explicit HPIS(Player* player);

    /**
     * @note Create-with System-Init
     */
    static void Init(Player* player);

    static void ThrowOut(const Player::Direction direction);

    template <typename T>
    static void ThrowOut(
        Dungeon::Map*           dungeonMap,
        const Player::Direction direction,
        const std::string&      imagePath
    );

private:
    static Player* m_Players;

private:
    /**
     * @note It's for check player that Presence of throwing weapons
     */
    static void IsExistWeaponThrow();
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HPIS_H
