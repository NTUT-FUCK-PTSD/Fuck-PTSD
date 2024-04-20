//
// Created by adven on 2024/4/7.
//

#ifndef FUCK_PTSD_SCOMPONENT_H
#define FUCK_PTSD_SCOMPONENT_H

#define int16t int16_t
#include <vector>

#include "../Weapon/Component.h"

namespace ToolSystem {

// Dig Level
struct DigLevel {
    explicit DigLevel(std::vector<std::size_t> _level)
        : level(_level) {};

    std::vector<std::size_t> level;
};

// Settings
// struct Settings {
//    explicit Settings(std::string &path, bool isThrow)
//        : imagePath(path),
//          isThrow(isThrow){};
//
//    bool isThrow;
//    std::string imagePath;
//};

// TBaseWeapon
struct TBaseShovel : DigLevel, Settings {
public:
    explicit TBaseShovel(std::vector<std::size_t> _level, std::string path,
                         bool isThrow)
        : DigLevel(_level),
          Settings(path, isThrow) {}
};
}; // namespace ToolSystem

#endif // FUCK_PTSD_SCOMPONENT_H
