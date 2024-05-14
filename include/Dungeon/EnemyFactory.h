#ifndef ENEMIESFACTORY_H
#define ENEMIESFACTORY_H

#include "DragonGreen.h"
#include "Dungeon/Enemies/Bat.h"
#include "Dungeon/Enemies/BlueSlime.h"
#include "Dungeon/Enemies/Ghost.h"
#include "Dungeon/Enemies/GreenSlime.h"
#include "Dungeon/Enemies/OrangeSlime.h"
#include "Dungeon/Enemies/Shopkeeper.h"
#include "Dungeon/Enemies/Skeleton.h"
#include "Dungeon/Enemies/Zombie.h"

namespace Dungeon {
class EnemyFactory final {
public:
    static std::shared_ptr<Enemy> CreateEnemy(
        const s_Enemy&                 u_Enemy,
        const std::shared_ptr<MapData> mapData
    ) {
        // clang-format off
        switch (u_Enemy.type) {
        case 0: return  std::make_shared<Enemies::GreenSlime>(u_Enemy, mapData);
        case 1: return  std::make_shared<Enemies::BlueSlime>(u_Enemy, mapData);
        case 2: return  std::make_shared<Enemies::OrangeSlime>(u_Enemy, mapData);
        case 3: return  std::make_shared<Enemies::Skeleton>(u_Enemy, mapData);
        case 4: return  std::make_shared<Enemies::Skeleton>(u_Enemy, mapData);
        case 5: return  std::make_shared<Enemies::Skeleton>(u_Enemy, mapData);
        case 6: return  std::make_shared<Enemies::Bat>(u_Enemy, mapData);
        case 7: return  std::make_shared<Enemies::Bat>(u_Enemy, mapData);
        case 8: return  std::make_shared<Enemies::Bat>(u_Enemy, mapData);
        case 11: return std::make_shared<Enemies::Ghost>(u_Enemy, mapData);
        case 12: return std::make_shared<Enemies::Zombie>(u_Enemy, mapData);
        case 600: return std::make_shared<Enemies::DragonGreen>(u_Enemy, mapData);
        // case 600: return std::make_shared<Enemies::Shopkeeper>(u_Enemy, mapData);
        default: return std::make_shared<Enemies::GreenSlime>(u_Enemy, mapData);
        }
        // clang-format on
    }
};
}  // namespace Dungeon

#endif  // ENEMIESFACTORY_H
