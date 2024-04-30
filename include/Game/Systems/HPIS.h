//
// Created by 陳世昂 on 2024/4/30.
//

#ifndef FUCK_PTSD_HPIS_H
#define FUCK_PTSD_HPIS_H

#include "Player.h"

#include "Player/Produce/Dagger.h"

#include "Util/Logger.hpp"

#include <memory>
#include "Warehouse/Throw.h"

#include "Player_config.h"

/**
 * @note This is "Handle Player-Interactive System"
 *
 */
namespace Game::Systems {
class HPIS final {
public:
    // explicit HPIS(Player* player);

    /**
     * @note Create-with System-Init
     */
    static void Init(Player* player);

private:
    static Player* m_Players;

private:
    static void IsExistWeaponThrow();
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HPIS_H
