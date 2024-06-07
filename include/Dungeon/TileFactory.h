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
    static std::shared_ptr<Tile> CreateTile(const s_Tile& _Tile) {
        if (_Tile.type <= 24) {
            if (_Tile.type == 8) {
                return std::make_shared<Tiles::FloorTar>(_Tile);
            } else if (_Tile.type == 9) {
                return std::make_shared<Tiles::StairsLockedMiniboss>(_Tile);
            } else if (_Tile.type == 23 || _Tile.type == 24) {
                return std::make_shared<Tiles::WirePhaseConductor>(_Tile);
            }
            return std::make_shared<Tiles::GeneralFloor>(_Tile);
        } else if (_Tile.type >= 50 && _Tile.type <= 52) {
            // side door
            if (_Tile.type == 52) {
                return std::make_shared<Tiles::DoorMetalSide>(_Tile);
            }
            return std::make_shared<Tiles::GeneralDoor>(_Tile);
        } else if (_Tile.type >= 100 && _Tile.type <= 123) {
            if (_Tile.type == 103 || _Tile.type == 106) {
                return std::make_shared<Tiles::GeneralDoor>(_Tile);
            } else if (_Tile.type == 111) {
                return std::make_shared<Tiles::DoorMetalFront>(_Tile);
            } else if (_Tile.type >= 112 && _Tile.type <= 117) {
                return std::make_shared<Tiles::NecroDancerStage>(_Tile);
            } else if (_Tile.type == 118) {
                return std::make_shared<Tiles::WireDoor>(_Tile);
            } else if (_Tile.type >= 120 && _Tile.type <= 123) {
                return std::make_shared<Tiles::ConductorWallPipe>(_Tile);
            }
            return std::make_shared<Tiles::GeneralWall>(_Tile);
        } else if (_Tile.type >= 1e6) {
            return std::make_shared<Tiles::GeneralTool>(_Tile);
        }
        LOG_ERROR(
            "TileFactory::CreateTile: Unknown tile type: "
            + std::to_string(_Tile.type)
        );
        return std::make_shared<Tiles::GeneralFloor>(s_Tile({0, 0, 0, 0, 0, 0})
        );
    }
};
}  // namespace Dungeon

#endif  // TILEFACTORY_H
