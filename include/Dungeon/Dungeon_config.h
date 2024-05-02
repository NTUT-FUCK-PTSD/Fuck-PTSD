//
// Created by adven on 2024/4/30.
//

#ifndef FUCK_PTSD_DUNGEON_CONFIG_H
#define FUCK_PTSD_DUNGEON_CONFIG_H

#include <Util/Image.hpp>
#include <iostream>
#include <string_view>

namespace Dungeon::config {
static constexpr std::string_view IMAGE_FULL_HEART_SM = ASSETS_DIR
    "/gui/TEMP_heart_small.png";

static constexpr std::string_view IMAGE_EMPTY_HEART_SM = ASSETS_DIR
    "/gui/TEMP_heart_empty_small.png";

/**
 * @note for emeny
 */
static std::shared_ptr<Util::Image> PTR_IMAGE_FULL_HEART_SM;

static std::shared_ptr<Util::Image> PTR_IMAGE_EMPTY_HEART_SM;
}  // namespace Dungeon::config

#endif  // FUCK_PTSD_DUNGEON_CONFIG_H
