#include "Dungeon/Map.h"

#include "Dungeon/EnemyFactory.h"

namespace Dungeon {
void Map::LoadEnemy() {
    m_MapData->ClearEnemies();

    std::size_t mapIndex = 0;
    for (auto& enemy : m_Level->GetEnemies()) {
        mapIndex = GamePostion2MapIndex({enemy.x, enemy.y});
        m_MapData->AddEnemy(
            mapIndex,
            EnemyFactory::CreateEnemy(enemy, m_MapData)
        );
    }

    for (auto& enemy : m_MapData->GetEnemyQueue()) {
        m_Children.push_back(enemy);
    }
}
}  // namespace Dungeon
