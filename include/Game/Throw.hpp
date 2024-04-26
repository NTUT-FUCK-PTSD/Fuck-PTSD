//
// Created by adven on 2024/4/26.
//

#ifndef FUCK_PTSD_THROW_HPP
#define FUCK_PTSD_THROW_HPP

#include <memory>
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

#include "Dungeon/Elements.h"
#include "Dungeon/Map.h"
#include "Dungeon/Tile.h"
#include "Dungeon/TileFactory.h"
#include "Dungeon/Tiles/GeneralTool.h"
#include "Settings/Helper.hpp"

namespace Game {
class Throw {
public:
    static void ThrowOut(Dungeon::Map* dungeonMap) {
        auto playerPosition = dungeonMap->GetMapData()->GetPlayerPosition();
        auto int_player = static_cast<glm::ivec2>(playerPosition);
        auto translateIdx = Settings::Helper::GamePosToMapIdx(playerPosition);

        const auto st =
            Dungeon::TileFactory::CreateTile(Dungeon::s_Tile{int_player.x, int_player.y, static_cast<std::size_t>(1e6), 0, 1, 0});
//        auto t = std::make_shared<Dungeon::Tiles::GeneralTool>(
//            st,
//            ASSETS_DIR "/items/weapon_dagger.png"
//        );

        auto a = std::make_shared<Util::Image>(ASSETS_DIR"/items/weapon_dagger.png");
        auto b = std::make_shared<Util::GameObject>();
        b->SetDrawable(a);
        b->SetZIndex(100);


        dungeonMap->GetMapData()->AddTile(translateIdx, st);
        LOG_INFO(dungeonMap->GetMapData()->GetTiles(translateIdx)[0]->GetZIndex());
        dungeonMap->GetMapData()->GetTiles(translateIdx)[0]->AddChild(b);
//        dungeonMap->GetMapData()->GetTiles(translateIdx)[1]->SetZIndex(1);
        LOG_INFO(dungeonMap->GetMapData()->GetTiles(translateIdx)[1]->GetZIndex());
        dungeonMap->CameraUpdate();


    }
};
}  // namespace Game

#endif  // FUCK_PTSD_THROW_HPP
