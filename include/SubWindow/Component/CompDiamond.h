//
// Created by adven on 2024/4/7.
//

#ifndef FUCK_PTSD_COMPDIAMOND_H
#define FUCK_PTSD_COMPDIAMOND_H
#include <iostream>

struct CompDiamond {
    explicit CompDiamond(uint16_t gainDiamond, uint16_t lostDiamond)
        : gainDiamond(gainDiamond),
          lostDiamond(lostDiamond){};

    uint16_t gainDiamond;
    uint16_t lostDiamond;
};
#endif // FUCK_PTSD_COMPDIAMOND_H
