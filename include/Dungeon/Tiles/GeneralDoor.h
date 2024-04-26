#ifndef GENERALDOOR_H
#define GENERALDOOR_H

#include <memory>
#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralDoor : public Tile {
public:
    GeneralDoor(const s_Tile& u_Tile, const bool generaldoor = true);
    GeneralDoor(
        const s_Tile&      u_Tile,
        const std::string& filePath,
        const bool         GeneralDoor = true
    );
    virtual ~GeneralDoor() override = default;

    bool IsWall() override { return false; };
    bool IsDoor() override { return true; };

    void SetOverlay(bool visible) override;

private:
    void init(const bool general);

    std::shared_ptr<Tile> m_Floor;
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // GeneralDoor_H
