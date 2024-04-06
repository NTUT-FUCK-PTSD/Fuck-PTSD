//
// Created by adven on 2024/4/6.
//

#ifndef FUCK_PTSD_BROADSWORD_H
#define FUCK_PTSD_BROADSWORD_H

#include "IBaseWeapon.h"

class Broadsword final : public IBaseWeapon {
public:
    explicit Broadsword();

    std::string GetItemImage() override {
        return ASSETS_DIR "/items/weapon_broadsword.png";
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

#endif // FUCK_PTSD_BROADSWORD_H
