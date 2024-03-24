//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_SHOVEL_H
#define FUCK_PTSD_SHOVEL_H

#include "pch_extream.h"

class Shovel final {
public:
    explicit Shovel();

    void setItem();

    void getItem();

private:
    std::string m_imagePathWindow = "";
    std::string m_imagePathItem = "";
};

#endif // FUCK_PTSD_SHOVEL_H
