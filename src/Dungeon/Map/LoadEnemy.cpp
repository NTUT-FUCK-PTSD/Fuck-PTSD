#include "Dungeon/Map.h"

#include "Dungeon/EnemyFactory.h"

namespace Dungeon {
void Map::LoadEnemy() {
    m_MapData->ClearEnemies();

    std::size_t mapIndex = 0;
    for (auto& enemy : m_Level->GetEnemies()) {
        mapIndex = GamePostion2MapIndex({enemy.x, enemy.y});
        auto _enemy = EnemyFactory::CreateEnemy(enemy, m_MapData);
        m_MapData->AddEnemy(mapIndex, _enemy);
        m_EnemyHead->AddChild(_enemy);
    }
}
}  // namespace Dungeon
