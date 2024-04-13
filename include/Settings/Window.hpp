#ifndef FUCK_PTSD_WINDOW_HPP
#define FUCK_PTSD_WINDOW_HPP

#include "config.hpp"

constexpr double DUNGEON_TILE_WIDTH = 24.0;
constexpr double DUNGEON_COL_NUMBER = 20.0;
constexpr double DUNGEON_ROW_NUMBER =
    (DUNGEON_COL_NUMBER * (double(WINDOW_HEIGHT) / double(WINDOW_WIDTH)));
constexpr double DUNGEON_SCALE =
    ((double(WINDOW_WIDTH) / DUNGEON_COL_NUMBER) / DUNGEON_TILE_WIDTH);

#endif // FUCK_PTSD_WINDOW_HPP
