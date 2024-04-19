//
// Created by adven on 2024/4/6.
//

#ifndef FUCK_PTSD_ENTITYRAPIER_H
#define FUCK_PTSD_ENTITYRAPIER_H

#include <iostream>

#include "Component.h"

namespace ToolSystem {
class EntityRapier final : public TBaseWeapon {
public:
    explicit EntityRapier();

private:
    // Damage
    const static int16_t normal = 1;
    const static int16_t blood = 1;
    const static int16_t glass = 4;
    const static int16_t golden = 1;
    inline const static std::string obsidian = "1-3";
    const static int16_t titanium = 2;

    // Settings
    const static bool isThrow = false;
    inline const static std::string ImagePath =
        ASSETS_DIR "/items/weapon_rapier.png";
};
}; // namespace ToolSystem
#endif // FUCK_PTSD_ENTITYRAPIER_H
