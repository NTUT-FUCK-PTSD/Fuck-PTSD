//
// Created by adven on 2024/4/7.
//

#ifndef FUCK_PTSD_ENTITYSHOVEL_H
#define FUCK_PTSD_ENTITYSHOVEL_H

#include "SComponent.h"

namespace ToolSystem {
class EntityShovel final : public TBaseShovel {
public:
    explicit EntityShovel();

    virtual ~EntityShovel() = default;
private:

    // Dig Level
    inline const static std::vector<std::size_t> level = {1};

    // Settings
    const static bool m_IsThrow = false;
    inline const static std::string ImagePath = ASSETS_DIR"/items/shovel_basic.png";
};
} // namespace ToolSystem

#endif // FUCK_PTSD_ENTITYSHOVEL_H
