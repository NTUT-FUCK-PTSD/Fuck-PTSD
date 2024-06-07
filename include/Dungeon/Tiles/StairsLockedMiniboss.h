#ifndef STAIRSLOCKEDMINIBOSS_H
#define STAIRSLOCKEDMINIBOSS_H

#include "Dungeon/Tiles/GeneralFloor.h"

namespace Dungeon {
namespace Tiles {
class StairsLockedMiniboss : public GeneralFloor {
public:
    explicit StairsLockedMiniboss(
        const s_Tile& u_Tile,
        const bool    generalFloor = true
    );
    virtual ~StairsLockedMiniboss() override = default;
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // STAIRSLOCKEDMINIBOSS_H
