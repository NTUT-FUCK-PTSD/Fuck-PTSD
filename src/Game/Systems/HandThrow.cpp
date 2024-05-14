//
// Created by adven on 2024/5/12.
//
#include "Game/Systems/HandThrow.h"
#include <functional>
#include <utility>
#include "Game/Actions.h"
#include "HPIS.h"
#include "Hash.h"

namespace Game::Systems {
HandThrow::HandThrow(Dungeon::Map* dungeonMap)
    : m_dungeonMap(dungeonMap) {}

void HandThrow::Dispatch(
    const std::string& weaponType,
    Player::Direction  dire,
    const std::string& imagePath
) {
    auto dp = DP{dire, imagePath};

    switch (HashConvert(weaponType)) {
    case "Dagger"_hash: Dagger(dp); break;

    case "Spear"_hash:
        Spear(dp);
        break;

        //    default: throw std::runtime_error("HandThrowHPMA not match type");
    }
}

void HandThrow::Dagger(DP dp) {
    auto [dire, imagePath] = std::move(dp);

    Game::Actions::ThrowOutWeapon<Game::Graphs::Dagger>(
        m_dungeonMap,
        dire,
        imagePath
    );
}

void HandThrow::Spear(DP dp) {
    auto [dire, imagePath] = std::move(dp);

    Game::Actions::ThrowOutWeapon<Game::Graphs::Spear>(
        m_dungeonMap,
        dire,
        imagePath
    );
}
}  // namespace Game::Systems
