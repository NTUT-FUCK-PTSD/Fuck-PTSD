//
// Created by adven on 2024/4/7.
//

#ifndef FUCK_PTSD_COMPCOIN_H
#define FUCK_PTSD_COMPCOIN_H
#include <iostream>

struct CompCoin {
    explicit CompCoin(uint16_t gainCoin, uint16_t lostCoin)
        : gainCoin(gainCoin),
          lostCoin(lostCoin){};

    uint16_t gainCoin;
    uint16_t lostCoin;
};
#endif // FUCK_PTSD_COMPCOIN_H
