#include "Dungeon/MapData.h"

#include <fmt/core.h>

namespace Dungeon {
MapData::MapData(const glm::vec2 &levelIndexMin, const glm::vec2 &levelIndexMax,
                 const glm::vec2 &size)
    : SimpleMapData(levelIndexMin, levelIndexMax, size) {
    m_Enemies.resize(GetSize().x * GetSize().y);
}

void MapData::AddEnemy(const std::size_t position,
                       const std::shared_ptr<Enemy> enemy) {
    m_Enemies.at(position) = enemy;
    SetHasEntity(position, true);
    m_EnemyQueue.push_back(enemy);
}

void MapData::RemoveEnemy(const std::size_t position) {
    if (m_Enemies.at(position) == nullptr) {
        return;
    }
    // m_Enemies.at(position)->SetVisible(false);
    m_EnemyQueue.erase(std::remove(m_EnemyQueue.begin(), m_EnemyQueue.end(),
                                   m_Enemies.at(position)),
                       m_EnemyQueue.end());
    m_Enemies.at(position) = nullptr;
    SetHasEntity(position, false);
}

void MapData::ClearEnemies() {
    m_Enemies.clear();
    m_Enemies.resize(GetSize().x * GetSize().y);
    m_HasEntity.clear();
    m_HasEntity.resize(GetSize().x * GetSize().y, false);
    m_EnemyQueue.clear();
}

std::vector<std::shared_ptr<Enemy>> MapData::GetEnemies() const {
    return m_Enemies;
}

std::shared_ptr<Enemy> MapData::GetEnemy(const std::size_t position) const {
    return m_Enemies.at(position);
}

std::vector<std::shared_ptr<Enemy>> MapData::GetEnemyQueue() const {
    auto v(m_EnemyQueue);
    sort(v.begin(), v.end(), EnemyCompare);
    return v;
}

bool MapData::EnemyCompare(std::shared_ptr<Enemy> &lhs,
                           std::shared_ptr<Enemy> &rhs) {
    std::string lhsPriority, rhsPriority;
    lhsPriority = lhs->GetLord() ? "2" : "1";
    rhsPriority = rhs->GetLord() ? "2" : "1";
    lhsPriority += fmt::format("{:0>2}", lhs->GetDamage());
    rhsPriority += fmt::format("{:0>2}", rhs->GetDamage());
    lhsPriority += fmt::format("{:0>2}", lhs->GetHealth());
    rhsPriority += fmt::format("{:0>2}", rhs->GetHealth());
    lhsPriority += fmt::format("{:0>2}", lhs->GetCoin());
    rhsPriority += fmt::format("{:0>2}", rhs->GetCoin());
    if (lhsPriority < rhsPriority) {
        return true;
    }
    else if (lhsPriority > rhsPriority) {
        return false;
    }

    return Heuristic(GetPlayerPosition(), lhs->GetGamePosition()) <
           Heuristic(GetPlayerPosition(), rhs->GetGamePosition());
}
} // namespace Dungeon
