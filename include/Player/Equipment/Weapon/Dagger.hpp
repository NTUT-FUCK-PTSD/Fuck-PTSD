//
// Created by adven on 2024/4/6.
//

#ifndef FUCK_PTSD_DAGGER_H
#define FUCK_PTSD_DAGGER_H

#include "IBaseWeapon.h"

class Dagger final : public IBaseWeapon {
public:
    explicit Dagger();
//    virtual ~Dagger() = 0;

    std::string GetItemImage() override {
        return ASSETS_DIR "/items/weapon_dagger.png";
    }

    Damage const GetDamage() override {
        struct IBaseWeapon::Damage damage;

        damage.normal = 1;
        damage.blood = 1;
        damage.glass = 4;
        damage.golden = 1;
        damage.obsidian = "1-3";
        damage.titanium = 2;

        return damage;
    }
};


#endif // FUCK_PTSD_DAGGER_H
