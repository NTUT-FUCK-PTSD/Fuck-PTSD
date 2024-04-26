//
// Created by 陳世昂 on 2024/4/26.
//

#ifndef FUCK_PTSD_ACTIONS_H
#define FUCK_PTSD_ACTIONS_H

#include "Util/Logger.hpp"
#include  "Util/Image.hpp"

#include "Game/Config.h"
#include "Game/Graphs/Dagger.h"
#include "Settings/Helper.hpp"
#include "Game/System.h"

namespace Game {
class Actions {
public:
    static void ThrowOutWeapon(Dungeon::Map *dungeonMap, const Player::Direction direction) {
        LOG_INFO("Throw out.");

        // get current player pos
        const auto [playerGP, playerMI] = Settings::Helper::GetPlayerPosDM();

        // translate direction
        const auto direMI = Settings::Helper::Direct2MI(direction);

        std::size_t weaponEndMI = 0;
        auto weaponNextPos = static_cast<glm::ivec2>(playerGP);

        while (true) {
            if (dungeonMap->GetMapData()->IsPositionWall(weaponNextPos + direMI)) {
                break;
            }

            // DOTO:
            weaponNextPos += direMI;
        }

        weaponEndMI = Settings::Helper::GamePosToMapIdx(weaponNextPos);

        const auto image = std::make_shared<Util::Image>(Config::IMAGE_DAGGER_PATH);
        const auto object = std::make_shared<Graphs::DaggerGameObj>();
        object->SetDrawable(image);

        System::AddWeapon(object, weaponEndMI);
    };
};
}

#endif  // FUCK_PTSD_ACTIONS_H
