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
    static void ThrowOutWeapon() {
        auto [playerGP, playerMI] = Settings::Helper::GetPlayerPosDM();

        const auto image = std::make_shared<Util::Image>(Config::IMAGE_DAGGER_PATH);
        const auto object = std::make_shared<Graphs::DaggerGameObj>();
        object->SetDrawable(image);

        System::AddWeapon(object, playerMI);
    };
};
}

#endif  // FUCK_PTSD_ACTIONS_H
