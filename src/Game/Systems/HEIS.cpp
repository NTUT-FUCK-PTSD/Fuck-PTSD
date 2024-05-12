//
// Created by adven on 2024/5/1.
//
#include "HEIS.h"
#include "Game/System.h"
#include "Game_config.h"
#include "Graphs/Dagger.h"
#include "Helper.hpp"

#include "Dungeon/Enemy.h"
#include "System.h"

auto Game::Systems::HEIS::Init(Dungeon::Map* dungeon) -> void {
    m_Map = dungeon;
}

auto Game::Systems::HEIS::DetectHealth(std::size_t mi) -> void {
    const auto& health = m_Map->GetMapData()->GetEnemy(mi)->GetHealth();
    if (health <= 0) {
        m_Map->RemoveEnemy(mi);
    }
}

auto Game::Systems::HEIS::MakeTile(
    glm::ivec2  direGP,
    glm::ivec2  playerGP,
    std::string weaponType
) -> void {
    std::size_t mi = 0;

    auto currGP = static_cast<glm::ivec2>(playerGP);

    // is wall
    while (m_Map->GetMapData()->IsPositionWall(currGP + direGP)) {
        mi = Settings::Helper::GamePosToMapIdx(currGP);

        if (m_Map->GetMapData()->IsEnemyEmpty(mi)) {
            m_Map->RemoveEnemy(mi);
        }

        currGP += direGP;

        //        // is wall?
        //        if (m_Map->GetMapData()->IsPositionWall(currGP + direGP)) {
        //            break;
        //        }
    }

    // renderer weapon on floor
    const auto pixelSize =
        ToolBoxs::CountImagePixel(Game::Config::IMAGE_DAGGER_PATH, 1, 2);
    const auto image = std::make_shared<SpriteSheet>(
        Config::IMAGE_DAGGER_PATH,
        pixelSize,
        std::vector<std::size_t>{0, 1},
        false,
        100,
        false,
        100
    );

    auto object = std::make_shared<Graphs::Dagger>();
    object->SetDrawable(image);

    System::AddWeapon(std::dynamic_pointer_cast<Graphs::IBase>(object), mi);
}

Dungeon::Map* Game::Systems::HEIS::m_Map = nullptr;
