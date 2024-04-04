#ifndef ENEMIESFACTORY_H
#define ENEMIESFACTORY_H

#include "Dungeon/Enemies/Bat.h"
#include "Dungeon/Enemies/BlueSlime.h"
#include "Dungeon/Enemies/GreenSlime.h"
#include "Dungeon/Enemies/OrangeSlime.h"
#include "Dungeon/Enemies/RedBat.h"
#include "Dungeon/Enemies/Skeleton.h"
#include "Dungeon/Enemies/Zombie.h"

namespace Dungeon {
class EnemyFactory final {
public:
    static std::shared_ptr<Enemy>
    CreateEnemy(const s_Enemy &u_Enemy,
                const std::shared_ptr<SimpleMapData> &simpleMapData) {
        switch (u_Enemy.type) {
        case 0:
            return std::make_shared<Enemies::GreenSlime>(u_Enemy,
                                                         simpleMapData);
        case 1:
            return std::make_shared<Enemies::BlueSlime>(u_Enemy, simpleMapData);
        case 2:
            return std::make_shared<Enemies::OrangeSlime>(u_Enemy,
                                                          simpleMapData);
        case 3:
            return std::make_shared<Enemies::Skeleton>(u_Enemy, simpleMapData);
        case 4:
            return std::make_shared<Enemies::Skeleton>(u_Enemy, simpleMapData);
        case 5:
            return std::make_shared<Enemies::Skeleton>(u_Enemy, simpleMapData);
        case 6:
            return std::make_shared<Enemies::Bat>(u_Enemy, simpleMapData);
        case 7:
            return std::make_shared<Enemies::RedBat>(u_Enemy, simpleMapData);
        case 12:
            return std::make_shared<Enemies::Zombie>(u_Enemy, simpleMapData);

        default:
            return std::make_shared<Enemies::GreenSlime>(u_Enemy,
                                                         simpleMapData);
        }
    }
};
} // namespace Dungeon

#endif // ENEMIESFACTORY_H
