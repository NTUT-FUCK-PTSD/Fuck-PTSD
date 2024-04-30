//
// Created by 陳世昂 on 2024/4/26.
//

#ifndef FUCK_PTSD_GAME_CONFIG_H
#define FUCK_PTSD_GAME_CONFIG_H

#include <string>

namespace Game {
namespace Config {
static const std::string IMAGE_DAGGER_PATH = ASSETS_DIR
    "/items/weapon_dagger.png";

/**
 * @note Special Function's stage
 */
enum class SF { INIT = 0, FIRST, SECOND, THRIED };
}  // namespace Config
}  // namespace Game

#endif  // FUCK_PTSD_GAME_CONFIG_H
