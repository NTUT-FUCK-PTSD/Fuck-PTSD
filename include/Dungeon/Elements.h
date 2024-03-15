#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "config.hpp"
#include "glm/glm.hpp"
#include <map>
#include <string>

namespace Dungeon {

constexpr double DUNGEON_TILE_WIDTH = 24.0;
constexpr double DUNGEON_COL_NUMBER = 20.0;
constexpr double DUNGEON_ROW_NUMBER =
    (DUNGEON_COL_NUMBER * (WINDOW_WIDTH / WINDOW_HEIGHT));
constexpr double DUNGEON_SCALE =
    ((WINDOW_WIDTH / DUNGEON_COL_NUMBER) / DUNGEON_TILE_WIDTH);

struct s_Tile {
    int x, y;
    size_t type, zone, torch, cracked;
};

struct s_Trap {
    int x, y;
    size_t type, subtype;
};

struct s_Enemy {
    int x, y;
    size_t type, beatDelay, lord;
};

struct s_Item {
    int x, y;
    std::string type;
    size_t bloodCost, saleCost, singleChoice;
};

struct s_Chest {
    int x, y;
    size_t saleCost, singleChoice, color, hidden;
    std::string contents;
};

struct s_Crate {
    int x, y;
    size_t type;
    std::string contents;
};

struct s_Shrine {
    int x, y;
    size_t type;
};
} // namespace Dungeon

const std::map<size_t, std::string> DUNGEON_TILETYPES = {
    {0, "floor_dirt1"},
    {2, "stairs"},
    {3, "TEMP_shop_floor"},
    {4, "TEMP_floor_water"},
    {5, "TEMP_floor_water"},
    {6, "stairs_locked"},
    {7, "TEMP_npc_floor"},

    {8, "floor_tar"},
    {9, "stairs_locked_miniboss"},
    {10, "TEMP_floor_hotcoal"},
    {11, "TEMP_floor_ice"},
    {12, "TEMP_floor_crystal"},
    {13, "TEMP_floor_geyser"},
    {15, "stairs_locked_diamond3"},

    {16, "stairs_locked_diamond9"},
    {17, "TEMP_floor_magnetic"},
    {18, "floor_lava"},
    {20, "wire"},

    {100, "wall_dirt_crypt"},
    {102, "end_of_world"},
    {103, "door_front"},
    {104, "wall_shop_crypt"},
    {105, "wall_shop_crypt_dark"},
    {106, "door_locked_front"},
    {107, "wall_stone_crypt"},

    {108, "wall_catacomb_crypt1"},
    {109, "boss_wall"},
    {111, "door_metal_front"},
    {112, "necrodancer_stage_green"},
    {113, "necrodancer_stage_turquoise"},
    {114, "necrodancer_stage_cyan"},
    {115, "necrodancer_stage_speaker1"},

    {116, "necrodancer_stage_spearker2"},
    {117, "necrodancer_stage_spearker3"},
    {118, "wire_door"}};

const std::map<size_t, glm::ivec2> DUNGEON_TILESIZES = {
    {0, {3, 2}},    {2, {1, 1}},   {3, {3, 1}},   {4, {3, 1}},
    {5, {3, 1}},    {6, {1, 1}},   {7, {3, 1}},

    {8, {3, 4}},    {9, {1, 1}},   {10, {3, 1}},  {11, {3, 1}},
    {12, {3, 2}},   {13, {3, 1}},  {15, {1, 1}},

    {16, {1, 1}},   {17, {3, 1}},  {18, {3, 5}},  {20, {16, 8}},

    {100, {16, 1}}, {102, {8, 1}}, {103, {1, 1}}, {104, {1, 1}},
    {105, {1, 1}},  {106, {1, 1}}, {107, {1, 1}},

    {108, {1, 1}},  {109, {5, 1}}, {111, {2, 2}}, {112, {6, 1}},
    {113, {6, 1}},  {114, {6, 1}}, {115, {6, 1}},

    {116, {6, 1}},  {117, {6, 1}}, {118, {1, 1}}};

#endif // ELEMENTS_H
