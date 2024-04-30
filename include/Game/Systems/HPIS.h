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

#include "Player_Config.h"

/**
 * @note This is "Handle Player-Interactive System"
 *
 */
namespace Game::Systems {
class HPIS final {
public:
    explicit HPIS(Player* player)
        : m_Players(player) {

          };

    void WeaponChange() {
        const auto& item = dynamic_cast<Dagger*>(
            m_Players->GetToolMod()->GetTool(2).get()
        );
        const auto& _throw = std::make_shared<Game::Warehouse::Throw>(Config::IMAGE_DAGGER_PATH);
        m_Players->GetToolMod()->AddTool(_throw);
    };

private:
    Player* m_Players;
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HPIS_H
