#ifndef GENERALWALL_H
#define GENERALWALL_H

#include "Dungeon/Tile.h"

namespace Dungeon {
namespace Tiles {
class GeneralWall : public Tile {
public:
    GeneralWall(const s_Tile& u_Tile, const bool generalWall = true);
    GeneralWall(
        const s_Tile&      u_Tile,
        const std::string& filePath,
        const bool         generalWall = true
    );
    virtual ~GeneralWall() override = default;

    bool IsWall() override { return true; };
    bool IsDoor() override { return false; };

protected:
    void UpdateTranslation() override;
};
}  // namespace Tiles
}  // namespace Dungeon

#endif  // GENERALWALL_H
