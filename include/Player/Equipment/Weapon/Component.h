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

//    explicit Damage(int16t nor, int16t blood, int16t glass, int16t golden,
//                    const char* obsidian, int16t titan)
//        : normal(nor),
//          blood(blood),
//          glass(glass),
//          golden(golden),
//          obsidian(obsidian),
//          titanium(titan) {}
explicit Damage(int16t nor, int16t blood, int16t glass, int16t golden)
    : normal(nor),
      blood(blood),
      glass(glass),
      golden(golden){};

    // Damage
    int16_t normal;
    int16_t blood;
    int16_t glass;
    int16_t golden;
    const char* obsidian;
    int16_t titanium;
};

// Settings
struct Settings {
    std::string imagePath;

    explicit Settings(const char* path)
        : imagePath(path){};
};

// TBaseWeapon
struct TBaseWeapon : Damage, Settings {
public:
//    explicit TBaseWeapon(int16t nor, int16t blood, int16t glass, int16t golden,
//                         const char* obsidian, int16t titan, const char* path)
//        : Damage(nor, blood, glass, golden, obsidian, titan),
//          Settings(path){};

    explicit TBaseWeapon(const char* path, int16t nor, int16t blood,
                         int16t glass, int16t golden)
        : Settings(path),
          Damage(nor, blood, glass, golden){};
};
}; // namespace ToolSystem

#endif // FUCK_PTSD_COMPONENT_H
