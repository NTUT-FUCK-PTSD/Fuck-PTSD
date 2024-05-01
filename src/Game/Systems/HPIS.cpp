#include "HPIS.h"
#include "ISC.h"
#include "Player.h"
#include "Settings/Helper.hpp"
#include "Signal.h"

// Game::Systems::HPIS::HPIS(Player* player)
//     : m_Players(player) {}
//     void
//     Game::Systems::HPIS::IsExistWeaponThrow() {
//     const auto& _throw = std::make_shared<Game::Warehouse::Throw>(
//         Config::IMAGE_DAGGER_PATH
//     );
//     m_Players->GetToolMod()->AddTool(_throw);
// }

void Game::Systems::HPIS::Init(Player* player) {
    m_Players = player;

    IsExistWeaponThrow();

    return;
}

void Game::Systems::HPIS::IsExistWeaponThrow() {
    const auto& _throw = std::make_shared<Game::Warehouse::Throw>(
        Config::IMAGE_DAGGER_PATH
    );
    m_Players->GetToolMod()->AddTool(_throw);
}

void Game::Systems::HPIS::ThrowOut(const Player::Direction direction) {
    LOG_INFO("Throw out.");

    const auto [playerGP, playerMI] = Settings::Helper::GetPlayerPosDM();
    const auto direGP = Settings::Helper::Direct2MI(direction);

    ISC::Handle(Signal::ADD_DROP_WEAPON, direGP, playerGP, "atds");
}

Player* Game::Systems::HPIS::m_Players = nullptr;
