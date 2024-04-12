#include "Dungeon/Tiles/GeneralWall.h"

namespace Dungeon {
namespace Tiles {
GeneralWall::GeneralWall(const s_Tile &u_Tile)
    : Tile(u_Tile) {
    m_MagicNumber = 7;
    m_ImgSize.y -= 1;
}
} // namespace Tiles
} // namespace Dungeon
