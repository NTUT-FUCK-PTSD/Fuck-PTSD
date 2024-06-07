#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include "Dungeon/Tiles/ConductorWallPipe.h"
#include "Dungeon/Tiles/DoorMetalFront.h"
#include "Dungeon/Tiles/DoorMetalSide.h"
#include "Dungeon/Tiles/FloorTar.h"
#include "Dungeon/Tiles/GeneralDoor.h"
#include "Dungeon/Tiles/GeneralFloor.h"
#include "Dungeon/Tiles/GeneralTool.h"
#include "Dungeon/Tiles/GeneralWall.h"
#include "Dungeon/Tiles/NecroDancerStage.h"
#include "Dungeon/Tiles/StairsLockedMiniboss.h"
#include "Dungeon/Tiles/WireDoor.h"
#include "Dungeon/Tiles/WirePhaseConductor.h"

namespace Dungeon {
class TileFactory final {
public:
    static std::shared_ptr<Tile> CreateTile(const s_Tile& u_Tile) {
        if (u_Tile.type <= 24) {
            if (u_Tile.type == 8) {
                return std::make_shared<Tiles::FloorTar>(u_Tile);
            } else if (u.type == 9) {
                return std::make_shared<Tiles::StairsLockedMiniboss>(u_Tile);
            } else if (u_Tile.type == 23 || u_Tile.type == 24) {
                return std::make_shared<Tiles::WirePhaseConductor>(u_Tile);
            }
            return std::make_shared<Tiles::GeneralFloor>(u_Tile);
        } else if (u_Tile.type >= 50 && u_Tile.type <= 52) {
            // side door
            if (u_Tile.type == 52) {
                return std::make_shared<Tiles::DoorMetalSide>(u_Tile);
            }
            return std::make_shared<Tiles::GeneralDoor>(u_Tile);
        } else if (u_Tile.type >= 100 && u_Tile.type <= 123) {
            if (u_Tile.type == 103 || u_Tile.type == 106) {
                return std::make_shared<Tiles::GeneralDoor>(u_Tile);
            } else if (u_Tile.type == 111) {
                return std::make_shared<Tiles::DoorMetalFront>(u_Tile);
            } else if (u_Tile.type >= 112 && u_Tile.type <= 117) {
                return std::make_shared<Tiles::NecroDancerStage>(u_Tile);
            } else if (u_Tile.type == 118) {
                return std::make_shared<Tiles::WireDoor>(u_Tile);
            } else if (u_Tile.type >= 120 && u_Tile.type <= 123) {
                return std::make_shared<Tiles::ConductorWallPipe>(u_Tile);
            }
            return std::make_shared<Tiles::GeneralWall>(u_Tile);
        } else if (u_Tile.type >= 1e6) {
            return std::make_shared<Tiles::GeneralTool>(u_Tile);
        }
        LOG_ERROR(
            "TileFactory::CreateTile: Unknown tile type: "
            + std::to_string(u_Tile.type)
        );
        return std::make_shared<Tiles::GeneralFloor>(s_Tile({0, 0, 0, 0, 0, 0})
        );
    }
};
}  // namespace Dungeon

#endif  // TILEFACTORY_H
