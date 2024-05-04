//
// Created by adven on 2024/5/1.
//
#include "HEIS.h"

#include "Dungeon/Enemy.h"

auto Game::Systems::HEIS::Init(Dungeon::Map* dungeon) -> void {
    m_Map = dungeon;
}

auto Game::Systems::HEIS::DetectHealth(std::size_t mi) -> void {
    const auto& health = m_Map->GetMapData()->GetEnemy(mi)->GetHealth();
    if (health <= 0) {
        m_Map->RemoveEnemy(mi);
    }
}

Dungeon::Map* Game::Systems::HEIS::m_Map = nullptr;
