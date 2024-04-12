#ifndef FLOORTAR_H
#define FLOORTAR_H

#include "Dungeon/Tiles/GeneralFloor.h"

namespace Dungeon {
namespace Tiles {
class FloorTar final : public GeneralFloor {
public:
    explicit FloorTar(const s_Tile &u_Tile);
    virtual ~FloorTar() override = default;
};
} // namespace Tiles
} // namespace Dungeon

#endif // FLOORTAR_H
