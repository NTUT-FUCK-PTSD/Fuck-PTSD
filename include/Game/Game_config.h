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

static constexpr std::string_view MUSIC_ZONE_12 = ASSETS_DIR
    "/music/zone1_2.ogg";

static constexpr std::string_view MUSIC_ZONE_13 = ASSETS_DIR
    "/music/zone1_3.ogg";

static constexpr std::string_view TEMPO_ZONE_12 = ASSETS_DIR
    "/music/zone1_2.txt";

static constexpr std::string_view TEMPO_ZONE_13 = ASSETS_DIR
    "/music/zone1_3.txt";

static std::size_t idx = 0;

/**
 * @note Special Function's stage
 */
enum class SF { INIT = 0, FIRST, SECOND, THRIED };
}  // namespace Config
}  // namespace Game

#endif  // FUCK_PTSD_GAME_CONFIG_H
