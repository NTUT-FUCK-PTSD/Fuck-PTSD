//
// Created by adven on 2024/4/28.
//

#ifndef FUCK_PTSD_PLAYER_CONFIG_H
#define FUCK_PTSD_PLAYER_CONFIG_H

#include <glm/vec2.hpp>
#include <string_view>

#include "Dungeon/Map.h"
#include "Util/Color.hpp"

namespace Players::Config {
static constexpr std::string_view IMAGE_SLOT_BOMB = ASSETS_DIR
    "/gui/hud_slot_bomb.png";

static constexpr std::string_view IMAGE_BOMB = ASSETS_DIR "/items/bomb.png";

static constexpr std::string_view STY_FONT = ASSETS_DIR
    "/font/necrosans-6/necrosans-6.otf";

static constexpr std::string_view IMAGE_SLOT_SHOVEL = ASSETS_DIR
    "/gui/hud_slot_1.png";

static constexpr std::string_view IMAGE_SHOVEL_BASIC = ASSETS_DIR
    "/items/shovel_basic.png";

static constexpr std::string_view IMAGE_SLOT_DAGGER = ASSETS_DIR
    "/gui/hud_slot_2.png";

static constexpr std::string_view IMAGE_DAGGER = ASSETS_DIR "/items/weapon_dagger.png";

static constexpr glm::vec2 VAL_FONT_SCALE = {5, 5};

static constexpr std::size_t VAL_FONT_SIZE = 6;

static constexpr float VAL_ZINDEX = 99.0f;

static constexpr glm::vec2 VAL_INITPOS = {0, 0};

static const glm::vec2 VAL_SCALE = {DUNGEON_SCALE, DUNGEON_SCALE};

static const Util::Color VAL_COLOR_WHITE = Util::Color(255, 255, 255);

}  // namespace Players::Config

#endif  // FUCK_PTSD_PLAYER_CONFIG_H
