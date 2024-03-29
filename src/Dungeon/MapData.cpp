#include "Dungeon/MapData.h"

namespace Dungeon {
MapData::MapData(const glm::vec2 &levelIndexMin, const glm::vec2 &levelIndexMax,
                 const glm::vec2 &size)
    : SimpleMapData(levelIndexMin, levelIndexMax, size) {
    m_Enemies.resize(GetSize().x * GetSize().y);
}

void MapData::AddEnemy(const size_t &position,
                       const std::shared_ptr<Enemy> &enemy) {
    m_Enemies.at(position).push_back(enemy);
}

void MapData::RemoveEnemy(const size_t &position,
                          const std::shared_ptr<Enemy> &enemy) {
    m_Enemies.at(position).erase(std::remove(m_Enemies.at(position).begin(),
                                             m_Enemies.at(position).end(),
                                             enemy),
                                 m_Enemies.at(position).end());
}

void MapData::PopbackEnemy(const size_t &position) {
    m_Enemies.at(position).pop_back();
}

bool MapData::IsEnemiesEmpty(const size_t &position) const {
    return m_Enemies.at(position).empty();
}

std::vector<std::shared_ptr<Enemy>>
MapData::GetEnemies(const size_t &position) const {
    return m_Enemies.at(position);
}

std::shared_ptr<Enemy> MapData::GetEnemyBack(const size_t &position) const {
    return m_Enemies.at(position).back();
}

} // namespace Dungeon
