//
// Created by adven on 2024/4/7.
//

#ifndef FUCK_PTSD_COMPHEART_H
#define FUCK_PTSD_COMPHEART_H
#include <iostream>

struct CompHeart {
    explicit CompHeart(float gainHP, float lostHP)
        : gainHP(gainHP),
          lostHP(lostHP){};

    float gainHP;
    float lostHP;
};
#endif // FUCK_PTSD_COMPHEART_H
