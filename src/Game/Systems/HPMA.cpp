//
// Created by adven on 2024/5/12.
//
#include "Game/Systems/HPMA.h"
#include <functional>
#include "Actions.h"
#include "Hash.h"

namespace Game::Systems {
HPMA::HPMA(Dungeon::Map* dungeonMap)
    : m_dungeonMap(dungeonMap) {}

void HPMA::Dispatch(
    const std::string& weaponType,
    Player::Direction  dire,
    const std::string& imagePath
) {
    switch (HashConvert(weaponType)) {
    case "Dagger"_hash:
        Game::Actions::ThrowOutWeapon<Game::Graphs::Dagger>(
            m_dungeonMap,
            dire,
            imagePath
        );
        break;

    case "Spear"_hash:
        Game::Actions::ThrowOutWeapon<Game::Graphs::Spear>(
            m_dungeonMap,
            dire,
            imagePath
        );
        break;

    default: throw std::runtime_error("HPMA not match type");
    }
}
}  // namespace Game::Systems
