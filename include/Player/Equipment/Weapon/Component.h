//
// Created by adven on 2024/4/6.
//

#ifndef FUCK_PTSD_COMPONENT_H
#define FUCK_PTSD_COMPONENT_H

#define int16t int16_t
#include <iostream>

namespace ToolSystem {

// Damage
struct Damage {

    explicit Damage(int16t nor, int16t blood, int16t glass, int16t golden,
                    std::string obsidian, int16t titan)
        : normal(nor),
          blood(blood),
          glass(glass),
          golden(golden),
          obsidian(obsidian),
          titanium(titan) {}

    // Damage
    int16_t normal;
    int16_t blood;
    int16_t glass;
    int16_t golden;
    std::string obsidian;
    int16_t titanium;
};

// Settings
struct Settings {
    explicit Settings(std::string &path, bool isThrow)
        : imagePath(path),
          isThrow(isThrow){};

    std::string imagePath;
    bool isThrow;
};

// TBaseWeapon
struct TBaseWeapon : Damage, Settings {
public:
    explicit TBaseWeapon(int16t nor, int16t blood, int16t glass, int16t golden,
                         std::string obsidian, int16t titan, std::string path,
                         bool isThrow)
        : Damage(nor, blood, glass, golden, obsidian, titan),
          Settings(path, isThrow){};
};
}; // namespace ToolSystem

#endif // FUCK_PTSD_SCOMPONENT_H
