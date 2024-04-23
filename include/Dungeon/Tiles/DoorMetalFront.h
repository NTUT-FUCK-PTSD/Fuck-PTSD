#ifndef DOORMETALFRONT_H
#define DOORMETALFRONT_H

#include "Dungeon/Tiles/GeneralDoorFront.h"

namespace Dungeon {
namespace Tiles {
class DoorMetalFront final : public GeneralDoorFront {
public:
    explicit DoorMetalFront(const s_Tile& u_Tile);
    virtual ~DoorMetalFront() override = default;
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // DOORMETALFRONT_H
