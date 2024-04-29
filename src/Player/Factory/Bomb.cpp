//
// Created by 陳世昂 on 2024/4/29.
//

#include "Factory/Bomb.h"
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
    const auto slotSize = Settings::Helper::
}
