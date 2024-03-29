#ifndef MAP_DATA_H
#define MAP_DATA_H

#include "Dungeon/Enemy.h"
#include "Dungeon/SimpleMapData.h"
#include <vector>

namespace Dungeon {
class MapData final : public SimpleMapData {
public:
    MapData(const glm::vec2 &levelIndexMin, const glm::vec2 &levelIndexMax,
            const glm::vec2 &size);

    void AddEnemy(const size_t &position, const std::shared_ptr<Enemy> &enemy);
    void RemoveEnemy(const size_t &position,
                     const std::shared_ptr<Enemy> &enemy);
    void PopbackEnemy(const size_t &position);
    bool IsEnemiesEmpty(const size_t &position) const;
    std::vector<std::shared_ptr<Enemy>>
    GetEnemies(const size_t &position) const;
    std::shared_ptr<Enemy> GetEnemyBack(const size_t &position) const;

private:
    std::vector<std::vector<std::shared_ptr<Enemy>>> m_Enemies;
};
} // namespace Dungeon

#endif // MAP_DATA_H
