#include "Dungeon/MapData.h"

namespace Dungeon {
MapData::MapData(const glm::vec2 &levelIndexMin, const glm::vec2 &levelIndexMax,
                 const glm::vec2 &size)
    : SimpleMapData(levelIndexMin, levelIndexMax, size) {
    m_Enemies.resize(GetSize().x * GetSize().y);
}

void MapData::AddEnemy(const size_t &position,
                       const std::shared_ptr<Enemy> &enemy) {
    m_Enemies.at(position) = enemy;
    SetHasEntity(position, true);
}

void MapData::RemoveEnemy(const size_t &position) {
    m_Enemies.at(position) = nullptr;
    if (m_Enemies.at(position) == nullptr) {
        SetHasEntity(position, false);
    }
}

std::vector<std::shared_ptr<Enemy>> MapData::GetEnemies() const {
    return m_Enemies;
}

std::shared_ptr<Enemy> MapData::GetEnemy(const size_t &position) const {
    return m_Enemies.at(position);
}

} // namespace Dungeon
