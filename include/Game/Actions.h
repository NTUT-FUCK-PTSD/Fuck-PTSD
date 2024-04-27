//
// Created by 陳世昂 on 2024/4/26.
//

#ifndef FUCK_PTSD_ACTIONS_H
#define FUCK_PTSD_ACTIONS_H

#include "Util/Image.hpp"
#include "Util/Logger.hpp"

#include "Game/Config.h"
#include "Game/Graphs/Dagger.h"
#include "Game/System.h"
#include "Settings/Helper.hpp"
#include "SpriteSheet.hpp"

namespace Game {
class Actions {
public:
    static void ThrowOutWeapon(
        Dungeon::Map*           dungeonMap,
        const Player::Direction direction
    ) {
        LOG_INFO("Throw out.");

        // get current player pos
        const auto [playerGP, playerMI] = Settings::Helper::GetPlayerPosDM();

        // translate direction
        const auto direMI = Settings::Helper::Direct2MI(direction);

        std::size_t weaponEndMI = 0;
        const auto& mapdata = dungeonMap->GetMapData();
        auto        weaponNextPos = static_cast<glm::ivec2>(playerGP);

        // looking for wall to stop flying weapon
        while (true) {
            weaponEndMI = Settings::Helper::GamePosToMapIdx(weaponNextPos);
            if (dungeonMap->GetMapData()->IsPositionWall(
                    weaponNextPos + direMI
                )) {
                break;
            }

            // DOTO:
            if (mapdata->IsHasEntity(weaponEndMI)) {
                dungeonMap->RemoveEnemy(weaponEndMI);
            };

            weaponNextPos += direMI;
        }

        const auto pixelSize =
            ToolBoxs::CountImagePixel(Config::IMAGE_DAGGER_PATH, 1, 2);
        const auto image = std::make_shared<SpriteSheet>(
            Config::IMAGE_DAGGER_PATH,
            pixelSize,
            std::vector<std::size_t>{0, 1},
            false,
            100,
            false,
            100
        );
        const auto object = std::make_shared<Graphs::DaggerGameObj>();
        object->SetDrawable(image);

        System::AddWeapon(object, weaponEndMI);
    };
};
}  // namespace Game

#endif  // FUCK_PTSD_ACTIONS_H