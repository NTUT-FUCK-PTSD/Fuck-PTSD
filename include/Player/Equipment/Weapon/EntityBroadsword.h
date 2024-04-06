//
// Created by adven on 2024/4/6.
//

#ifndef FUCK_PTSD_ENTITYBROADSWORD_H
#define FUCK_PTSD_ENTITYBROADSWORD_H

#include "Component.h"

namespace ToolSystem{
class EntityBroadsword final : public TBaseWeapon  {
public:
    explicit EntityBroadsword();

//    virtual ~EntityBroadsword() = default;

private:

    // Damage
    int16_t normal = 1;
    int16_t blood = 1;
    int16_t glass = 4;
    int16_t golden = 1;
    std::string obsidian = "1-3";
    int16_t titanium = 2;

    // Settings
    std::string a = ASSETS_DIR "/items/weapon_broadsword.png";
};
}
#endif // FUCK_PTSD_ENTITYBROADSWORD_H

