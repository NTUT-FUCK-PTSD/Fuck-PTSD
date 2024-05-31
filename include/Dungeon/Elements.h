#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <map>
#include <string>

#include "config.hpp"

#include "glm/glm.hpp"

namespace Dungeon {

struct s_Tile {
    int         x, y;
    std::size_t type, zone, torch, cracked;
};

struct s_Trap {
    int         x, y;
    std::size_t type, subtype;
};

struct s_Enemy {
    int         x, y;
    std::size_t type, beatDelay, lord;
};

struct s_Item {
    int         x, y;
    std::string type;
    std::size_t bloodCost, saleCost, singleChoice;
};

struct s_Chest {
    int         x, y;
    std::size_t saleCost, singleChoice, color, hidden;
    std::string contents;
};

struct s_Crate {
    int         x, y;
    std::size_t type;
    std::string contents;
};

struct s_Shrine {
    int         x, y;
    std::size_t type;
};
}  // namespace Dungeon

const std::map<std::size_t, std::string> DUNGEON_TILETYPES = {
  {0, "floor_dirt1"},
  {1, "floor_dirt2"},  // type 1 and type 0 are different png files
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
  {20, "wire"},  // NOT IMPLEMENTED
  {21, "floor_rising"},
  {22, "floor_receded"},
  {23, "wire_phase1_conductor"},  // NOT IMPLEMENTED
  {24, "wire_phase2_conductor"},  // NOT IMPLEMENTED
  {25, "boss_floor_A"},
  {26, "boss_floor_conductor"},

  {50, "door_side"},         // virtual door type
  {51, "door_locked_side"},  // virtual door type
  {52, "door_metal_side"},   // virtual door type

  {100, "wall_dirt_crypt"},
  {101, "wall_dirt_crypt"},  // type 101 is second index of
                             // wall_dirt_crypt(type 100)
  {102, "end_of_world"},
  {103, "door_front"},
  {104, "wall_shop_crypt"},
  {105, "wall_shop_crypt_dark"},
  {106, "door_locked_front"},
  {107, "wall_stone_crypt"},

  {108, "wall_catacomb_crypt1"},
  {109, "boss_wall"},
  {110, "wall_shop_crypt_cracked"},  // same as wall_shop_crypt(type 104) with
                                     // cracks
  {111, "door_metal_front"},
  {112, "necrodancer_stage_green"},      // NOT IMPLEMENTED
  {113, "necrodancer_stage_turquoise"},  // NOT IMPLEMENTED
  {114, "necrodancer_stage_cyan"},       // NOT IMPLEMENTED
  {115, "necrodancer_stage_speaker1"},   // NOT IMPLEMENTED

  {116, "necrodancer_stage_spearker2"},  // NOT IMPLEMENTED
  {117, "necrodancer_stage_spearker3"},  // NOT IMPLEMENTED
  {118, "wire_door"},
  {119, "wall_dirt_crypt"},       // same as type 101
  {120, "conductor_wall_pipe1"},  // NOT IMPLEMENTED
  {121, "conductor_wall_pipe2"},  // NOT IMPLEMENTED
  {122, "conductor_wall_pipe3"},  // NOT IMPLEMENTED
  {123, "conductor_wall_pipe4"}   // NOT IMPLEMENTED
};

const std::unordered_map<std::size_t, std::string> DUNGEON_TOOLTYPE = {
  {1e6, "weapon_dagger"}
};

const std::unordered_map<std::size_t, glm::ivec2> DUNGEON_TOOLSIZES = {
  {static_cast<std::size_t>(1e6), {1, 2}},
};

const std::map<std::size_t, glm::ivec2> DUNGEON_TILESIZES = {
  {0, {3, 2}},    {1, {3, 2}},    {2, {1, 1}},   {3, {3, 1}},    {4, {3, 1}},
  {5, {3, 1}},    {6, {1, 1}},    {7, {3, 1}},

  {8, {3, 4}},    {9, {1, 1}},    {10, {3, 1}},  {11, {3, 1}},   {12, {3, 2}},
  {13, {3, 1}},   {15, {1, 1}},

  {16, {1, 1}},   {17, {3, 1}},   {18, {3, 5}},  {20, {16, 8}},  {21, {3, 1}},
  {22, {3, 1}},   {23, {7, 5}},   {24, {3, 5}},  {25, {3, 2}},   {26, {3, 2}},

  {50, {1, 1}},   {51, {1, 1}},   {52, {2, 1}},

  {100, {16, 1}}, {101, {16, 1}}, {102, {8, 1}}, {103, {1, 1}},  {104, {1, 1}},
  {105, {1, 1}},  {106, {1, 1}},  {107, {1, 1}},

  {108, {1, 1}},  {109, {5, 1}},  {110, {1, 1}}, {111, {2, 2}},  {112, {6, 1}},
  {113, {6, 1}},  {114, {6, 1}},  {115, {6, 1}},

  {116, {6, 1}},  {117, {6, 1}},  {118, {1, 1}}, {119, {16, 1}}, {120, {1, 1}},
  {121, {1, 1}},  {122, {1, 1}},  {123, {1, 1}}
};

#endif  // ELEMENTS_H
