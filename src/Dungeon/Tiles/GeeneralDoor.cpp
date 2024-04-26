#include "Dungeon/Tiles/GeneralDoor.h"

#include "Dungeon/Tiles/GeneralFloor.h"
#include "Elements.h"

namespace Dungeon {
namespace Tiles {
GeneralDoor::GeneralDoor(const s_Tile& u_Tile, const bool generalDoorFront)
    : Tile(u_Tile) {
    init(generalDoorFront);
}

GeneralDoor::GeneralDoor(
    const s_Tile&      u_Tile,
    const std::string& filePath,
    const bool         generalDoorFront
)
    : Tile(u_Tile, filePath) {
    init(generalDoorFront);
}

void GeneralDoor::init(const bool general) {
    m_ZIndex = m_ZIndex + 0.125f;
    m_MagicNumber = 7;
    if (general) {
        UpdateDrawable();
    }

    m_Floor = std::make_shared<GeneralFloor>(
        s_Tile({m_Tile.x, m_Tile.y, 0, m_Tile.zone, 0, m_Tile.cracked}),
        true
    );
    m_Floor->SetOverlay(false);
    AddChild(m_Floor);
}

void GeneralDoor::SetOverlay(bool visible) {
    Tile::SetOverlay(visible);
    m_Floor->SetOverlay(visible);
}
}  // namespace Tiles
}  // namespace Dungeon
