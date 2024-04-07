//
// Created by adven on 2024/4/7.
//

#ifndef FUCK_PTSD_RESOURCE_H
#define FUCK_PTSD_RESOURCE_H
#include <iostream>

#include "../Component/CompCoin.h"
#include "../Component/CompDiamond.h"
#include "../Component/CompHeart.h"

struct Resource : CompCoin, CompDiamond, CompHeart {
    explicit Resource(bool isReady, uint16_t gainDiamond, uint16_t lostDiamond,
                      uint16_t gainCoin, uint16_t lostCoin, float gainHP,
                      float lostHP)
        : isReady(isReady),
          CompCoin(gainDiamond, lostDiamond),
          CompDiamond(gainCoin, lostCoin),
          CompHeart(gainHP, lostHP){};

    bool isReady = false;
};

#endif // FUCK_PTSD_RESOURCE_H
