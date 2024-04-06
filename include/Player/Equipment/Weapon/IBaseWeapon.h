//
// Created by adven on 2024/4/6.
//

#ifndef FUCK_PTSD_IBASEWEAPON_H
#define FUCK_PTSD_IBASEWEAPON_H

#include <iostream>

class IBaseWeapon {
public:

    struct Damage {
        int normal;
        int blood;
        int glass;
        int golden;
        std::string obsidian;
        int titanium;
    };

    virtual Damage const GetDamage() = 0;
    virtual std::string GetItemImage() = 0;
//    virtual void SpecialFeature() = 0;
};

#endif // FUCK_PTSD_IBASEWEAPON_H
