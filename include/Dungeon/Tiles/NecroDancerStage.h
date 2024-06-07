#ifndef NECRODANCERSTAGE_H
#define NECRODANCERSTAGE_H

#include "Dungeon/Tiles/GeneralWall.h"

namespace Dungeon {
namespace Tiles {
class NecroDancerStage final : public GeneralWall {
public:
    NecroDancerStage(const s_Tile& _Tile);
    virtual ~NecroDancerStage() override = default;
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // NECRODANCERSTAGE_H
