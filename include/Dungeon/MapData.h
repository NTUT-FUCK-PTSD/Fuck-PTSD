#ifndef MAP_DATA_H
#define MAP_DATA_H

#include "Dungeon/Enemy.h"
#include "Dungeon/SimpleMapData.h"

namespace Dungeon {
class MapData final : public SimpleMapData {
public:
    MapData(const glm::vec2 &levelIndexMin, const glm::vec2 &levelIndexMax,
            const glm::vec2 &size);

    void AddEnemy(const std::size_t position, const std::shared_ptr<Enemy> enemy);
    void RemoveEnemy(const std::size_t position);
    void ClearEnemies();
    std::vector<std::shared_ptr<Enemy>> GetEnemies() const;
    std::shared_ptr<Enemy> GetEnemy(const std::size_t position) const;
    std::vector<std::shared_ptr<Enemy>> GetEnemyQueue() const;

protected:
    static bool EnemyCompare(std::shared_ptr<Enemy> &lhs,
                             std::shared_ptr<Enemy> &rhs);

private:
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::vector<std::shared_ptr<Enemy>> m_EnemyQueue;
};
} // namespace Dungeon

#endif // MAP_DATA_H
