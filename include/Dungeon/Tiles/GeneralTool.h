//
// Created by adven on 2024/4/26.
//

#ifndef FUCK_PTSD_GENERALTOOL_H
#define FUCK_PTSD_GENERALTOOL_H

#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralTool : public Tile {
public:
    explicit GeneralTool(
        s_Tile             u_tile,
        const std::string& filePath,
        const bool         generalFloor = true
    )
        : Tile(u_tile, filePath) {
        if (generalFloor) {
            UpdateDrawable();
        }
    };

    ~GeneralTool() override = default;

    bool IsWall() override { return false; };
    bool IsDoor() override { return false; };
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // FUCK_PTSD_GENERALTOOL_H
