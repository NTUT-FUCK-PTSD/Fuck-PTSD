#include "Dungeon/Tiles/NecroDancerStage.h"

namespace Dungeon {
namespace Tiles {
NecroDancerStage::NecroDancerStage(const s_Tile& u_Tile)
    : GeneralWall(u_Tile, (ASSETS_DIR "/level/necrodancer_stage.png"), false) {
    m_Index = m_Tile.type - 112;
    m_MagicNumber = 41;
    UpdateDrawable();
}
}  // namespace Tiles
}  // namespace Dungeon
