#include "Dungeon/Tiles/GeneralDoorFront.h"

namespace Dungeon {
namespace Tiles {
GeneralDoorFront::GeneralDoorFront(const s_Tile &u_Tile,
                                   const bool generalDoorFront)
    : Tile(u_Tile) {
    m_ZIndex = m_ZIndex + 1e-6;
    m_MagicNumber = 7;
    if (generalDoorFront) {
        UpdateDrawable();
    }
}

GeneralDoorFront::GeneralDoorFront(const s_Tile &u_Tile,
                                   const std::string &filePath,
                                   const bool generalDoorFront)
    : Tile(u_Tile, filePath) {
    m_ZIndex = m_ZIndex + 1e-6;
    m_MagicNumber = 7;
    if (generalDoorFront) {
        UpdateDrawable();
    }
}
} // namespace Tiles
} // namespace Dungeon
