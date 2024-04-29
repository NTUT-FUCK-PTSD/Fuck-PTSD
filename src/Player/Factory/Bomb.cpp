//
// Created by 陳世昂 on 2024/4/29.
//

#include "Factory/Bomb.h"
#include "Player/Config.h"
#include "Settings/Helper.hpp"
#include "SpriteSheet.hpp"

Bomb::Bomb(std::size_t number) {
    GenSlot();
    GenItem();
    GenFirstTextLine();
    GenSecondTextLine();

    SetVisible(false);
}

void Bomb::GenSlot() {
    const auto& obj = std::make_shared<Util::GameObject>();
    const auto& slot = std::make_shared<Util::Image>(
        static_cast<std::string>(Players::Config::IMAGE_SLOT_BOMB)
    );
}
