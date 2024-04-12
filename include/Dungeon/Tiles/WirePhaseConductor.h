#ifndef WIREPHASECONDUCTOR_H
#define WIREPHASECONDUCTOR_H

#include "Dungeon/Tiles/GeneralFloor.h"

namespace Dungeon {
namespace Tiles {
class WirePhaseConductor final : public GeneralFloor {
public:
    explicit WirePhaseConductor(const s_Tile &u_Tile);
    virtual ~WirePhaseConductor() override = default;
};
} // namespace Tiles
} // namespace Dungeon

#endif // WIREPHASECONDUCTOR_H
