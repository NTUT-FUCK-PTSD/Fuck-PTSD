//
// Created by adven on 2024/5/1.
//
#include "HEIS.h"
#include "Helper.hpp"

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

    auto&& currGP = static_cast<glm::ivec2>(playerGP);

    while (true) {
        mi = Settings::Helper::GamePosToMapIdx(currGP);

        // is wall?
        if (m_Map->GetMapData()->IsPositionWall(currGP + direGP)) {
            break;
        }

        if (m_Map->GetMapData()->IsHasEntity(mi)) {
            m_Map->RemoveEnemy(mi);
            currGP += direGP;
        }
    }

    const auto dropFloor = []() {

    };

    dropFloor();
}

Dungeon::Map* Game::Systems::HEIS::m_Map = nullptr;
