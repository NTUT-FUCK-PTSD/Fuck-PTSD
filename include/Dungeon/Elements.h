#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <map>
#include <string>

namespace Dungeon {

struct tile {
    int x, y;
    int type, zone, torch, cracked;
};

struct trap {
    int x, y;
    int type, subtype;
};

struct enemy {
    int x, y;
    int type, beatDelay, lord;
};

struct item {
    int x, y;
    std::string type;
    int bloodCost, saleCost, singleChoice;
};

struct chest {
    int x, y;
    int saleCost, singleChoice, color, hidden;
    std::string contents;
};

struct crate {
    int x, y;
    int type;
    std::string contents;
};

struct shrine {
    int x, y;
    int type;
};
} // namespace Dungeon

const std::map<int, std::string> tileTypes = {
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

#endif // ELEMENTS_H
