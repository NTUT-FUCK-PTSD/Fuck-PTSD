#ifndef WIREDOOR_H
#define WIREDOOR_H

#include "Dungeon/Tiles/GeneralDoor.h"

namespace Dungeon {
namespace Tiles {
class WireDoor final : public GeneralDoor {
public:
    explicit WireDoor(const s_Tile& u_Tile);
    virtual ~WireDoor() override = default;
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // WIREDOOR_H
