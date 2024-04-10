#ifndef MAP_DATA_H
#define MAP_DATA_H

#include "Dungeon/Enemy.h"
#include "Dungeon/SimpleMapData.h"
#include <deque>
#include <vector>

namespace Dungeon {
class MapData final : public SimpleMapData {
public:
    MapData(const glm::vec2 &levelIndexMin, const glm::vec2 &levelIndexMax,
            const glm::vec2 &size);

    void AddEnemy(const size_t &position, const std::shared_ptr<Enemy> &enemy);
    void RemoveEnemy(const size_t &position);
    std::vector<std::shared_ptr<Enemy>> GetEnemies() const;
    std::shared_ptr<Enemy> GetEnemy(const size_t &position) const;
    std::deque<std::shared_ptr<Enemy>> GetEnemiesQueue() const;

private:
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::deque<std::shared_ptr<Enemy>> m_EnemiesQueue;
};
} // namespace Dungeon

#endif // MAP_DATA_H
