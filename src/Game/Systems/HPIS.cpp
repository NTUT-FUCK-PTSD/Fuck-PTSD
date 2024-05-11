#include "HPIS.h"
#include "ISC.h"
#include "Player.h"
#include "Player_config.h"
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
        Players::Config::IMAGE_SPEAR.data(),
        "Spear"
    );
    //    m_Players->GetToolMod()->AddTool(_throw, "Throw", "Dagger");
    m_Players->GetToolMod()->AddTool(_throw, "THROW", "Spear");
}

void Game::Systems::HPIS::ThrowOut(const Player::Direction direction) {
    LOG_INFO("Throw out.");

    const auto [playerGP, playerMI] = Settings::Helper::GetPlayerPosDM();
    const auto direGP = Settings::Helper::Direct2MI(direction);

    ISC::Handle(Signal::ADD_DROP_WEAPON, direGP, playerGP, "atds");
}

template <typename T>
void Game::Systems::HPIS::ThrowOut(
    Dungeon::Map*           dungeonMap,
    const Player::Direction direction,
    const std::string&      imagePath
) {
    const auto [playerGP, playerMI] = Settings::Helper::GetPlayerPosDM();
    const auto direMI = Settings::Helper::Direct2MI(direction);

    std::size_t weaponEndMI = 0;
    const auto& mapdata = dungeonMap->GetMapData();
    auto        weaponNextPos = static_cast<glm::ivec2>(playerGP);

    weaponEndMI = Settings::Helper::GamePosToMapIdx(playerGP);

    while (true) {
        weaponEndMI = Settings::Helper::GamePosToMapIdx(weaponNextPos);
        if (dungeonMap->GetMapData()->IsPositionWall(weaponNextPos + direMI)) {
            break;
        }

        // DOTO:
        if (mapdata->IsEnemyEmpty(weaponEndMI)) {
            dungeonMap->RemoveEnemy(weaponEndMI);
        };

        weaponNextPos += direMI;
    }

    const auto pixelSize =
        ToolBoxs::CountImagePixel(Config::IMAGE_DAGGER_PATH, 1, 2);
    const auto image = std::make_shared<SpriteSheet>(
        /* Config::IMAGE_DAGGER_PATH, */
        imagePath,
        pixelSize,
        std::vector<std::size_t>{0, 1},
        false,
        100,
        false,
        100
    );

    const auto   object = std::make_shared<T>();
    const auto&& obj = dungeonMap->GetMapData()->GetTile(weaponEndMI);
    object->m_Transform.translation = obj->m_Transform.translation;
    object->m_Transform.scale = {3, 3};
    object->SetDrawable(image);

    object->SetZIndex(obj->GetZIndex() + 0.1f);

    dungeonMap->AddItem(weaponEndMI, std::move(object));
}

Player* Game::Systems::HPIS::m_Players = nullptr;
