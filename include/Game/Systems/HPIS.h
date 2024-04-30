//
// Created by 陳世昂 on 2024/4/30.
//

#ifndef FUCK_PTSD_HPIS_H
#define FUCK_PTSD_HPIS_H

#include "Player.h"

/**
 * @note This is "Handle Player-Interactive System"
 *
 */
namespace Game::Systems{
class HPIS final{
public:
    explicit HPIS(Player* player): m_Players(player) {

        };

    void WeaponChange() {

    };

private:
    Player* m_Players;
};
}

#endif  // FUCK_PTSD_HPIS_H
