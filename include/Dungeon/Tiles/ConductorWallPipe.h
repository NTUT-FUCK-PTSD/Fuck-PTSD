#ifndef CONDUCTORWALLPIPE_H
#define CONDUCTORWALLPIPE_H

#include "Dungeon/Tiles/GeneralWall.h"

namespace Dungeon {
namespace Tiles {
class ConductorWallPipe final : public GeneralWall {
public:
    explicit ConductorWallPipe(const s_Tile& u_Tile);
    virtual ~ConductorWallPipe() override = default;
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // CONDUCTORWALLPIPE_H
