#include "Dungeon/MapData.h"

#include "Dungeon/AStar.h"
#include "Dungeon/Enemy.h"

namespace Dungeon {
MapData::MapData(
    const glm::vec2& levelIndexMin,
    const glm::vec2& levelIndexMax,
    const glm::vec2& size
)
    : m_LevelIndexMin(levelIndexMin),
      m_LevelIndexMax(levelIndexMax),
      m_Size(size) {
    m_Tiles.resize(GetSize().x * GetSize().y);
    m_HasEntity.resize(GetSize().x * GetSize().y, false);

    m_Enemies.resize(GetSize().x * GetSize().y);
}

void MapData::AddEnemy(
    const std::size_t            position,
    const std::shared_ptr<Enemy> enemy
) {
    m_Enemies.at(position) = enemy;
    SetHasEntity(position, true);
    m_EnemyQueue.push_back(enemy);
}

void MapData::RemoveEnemy(const std::size_t position) {
    if (m_Enemies.at(position) == nullptr) {
        return;
    }
    // m_Enemies.at(position)->SetVisible(false);
    m_EnemyQueue.erase(
        std::remove(
            m_EnemyQueue.begin(),
            m_EnemyQueue.end(),
            m_Enemies.at(position)
        ),
        m_EnemyQueue.end()
    );
    m_Enemies.at(position) = nullptr;
    SetHasEntity(position, false);
}

void MapData::MoveEnemy(const std::size_t src, const std::size_t dest) {
    m_Enemies.at(dest) = m_Enemies.at(src);
    m_Enemies.at(src) = nullptr;
    SetHasEntity(src, false);
    SetHasEntity(dest, true);
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

std::vector<std::shared_ptr<Enemy>> MapData::GetUnsortedEnemies() const {
    return m_EnemyQueue;
}

bool MapData::EnemyCompare(
    std::shared_ptr<Enemy>& lhs,
    std::shared_ptr<Enemy>& rhs
) {
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
    } else if (lhsPriority > rhsPriority) {
        return false;
    }

    return lhs->Heuristic(lhs->GetPlayerPosition(), lhs->GetGamePosition())
           < rhs->Heuristic(rhs->GetPlayerPosition(), rhs->GetGamePosition());
}

void MapData::AddTile(
    const std::size_t           position,
    const std::shared_ptr<Tile> tile
) {
    m_Tiles.at(position) = tile;
    m_TilesQueue.emplace_back(tile);
}

void MapData::RemoveTile(const std::size_t position) {
    m_TilesQueue.erase(
        std::remove(
            m_TilesQueue.begin(),
            m_TilesQueue.end(),
            m_Tiles.at(position)
        ),
        m_TilesQueue.end()
    );
    m_Tiles.at(position).reset();
}

void MapData::ClearTiles() {
    m_Tiles.clear();
    m_Tiles.resize(GetSize().x * GetSize().y);
    m_TilesQueue.clear();
}

std::vector<std::shared_ptr<Tile>> MapData::GetTiles() const {
    return m_Tiles;
}

bool MapData::IsTilesEmpty(const std::size_t position) const {
    return !m_Tiles.at(position);
}

std::shared_ptr<Tile> MapData::GetTile(const std::size_t position) const {
    return m_Tiles.at(position);
}

glm::ivec2 MapData::GetLevelIndexMax() const {
    return m_LevelIndexMax;
}

glm::ivec2 MapData::GetLevelIndexMin() const {
    return m_LevelIndexMin;
}

void MapData::SetLevelIndexMax(const glm::ivec2& levelIndexMax) {
    m_LevelIndexMax = levelIndexMax;
}

void MapData::SetLevelIndexMin(const glm::ivec2& levelIndexMin) {
    m_LevelIndexMin = levelIndexMin;
}

std::size_t MapData::GamePosition2MapIndex(const glm::ivec2& position) const {
    return (position.x - GetLevelIndexMin().x + 1)
           + (position.y - GetLevelIndexMin().y + 1) * m_Size.x;
}

bool MapData::IsPositionValid(const glm::ivec2& position) const {
    return position.x >= GetLevelIndexMin().x
           && position.x <= GetLevelIndexMax().x
           && position.y >= GetLevelIndexMin().y
           && position.y <= GetLevelIndexMax().y;
}

bool MapData::IsHasEntity(const std::size_t position) const {
    return m_HasEntity.at(position);
}

bool MapData::IsWalkable(const std::size_t position) const {
    auto tile = GetTile(position);

    return tile && !tile->IsWall() && !tile->IsDoor()
           && !m_HasEntity.at(position);
}

bool MapData::IsPositionWalkable(const glm::ivec2& position) const {
    return IsPositionValid(position)
           && IsWalkable(GamePosition2MapIndex(position));
}

bool MapData::IsPositionDoor(const glm::ivec2& position) const {
    auto tile = GetTile(GamePosition2MapIndex(position));
    return IsPositionValid(position) && tile && tile->IsDoor();
}

bool MapData::IsPositionWall(const glm::ivec2& position) const {
    auto tile = GetTile(GamePosition2MapIndex(position));
    return IsPositionValid(position) && tile && tile->IsWall();
}

bool MapData::IsPositionCoin([[maybe_unused]] const glm::ivec2& position
) const {
    return false;
}

bool MapData::IsPositionDiamond([[maybe_unused]] const glm::ivec2& position
) const {
    return false;
}

bool MapData::IsPositionHeart([[maybe_unused]] const glm::ivec2& position
) const {
    return false;
}

bool MapData::IsPositionTool([[maybe_unused]] const glm::ivec2& position
) const {
    return false;
}

bool MapData::IsPositionPlayer(const glm::vec2& position) const {
    return position == m_PlayerPosition;
}

bool MapData::IsPositionInteractive(const glm::ivec2& position) const {
    auto tile = GetTile(GamePosition2MapIndex(position));
    return IsPositionValid(position) && tile
           && (IsPositionDoor(position) || IsPositionWall(position)
               || IsHasEntity(GamePosition2MapIndex(position))
               || IsPositionPlayer(position) || IsPositionCoin(position)
               || IsPositionDiamond(position) || IsPositionHeart(position)
               || IsPositionTool(position));
}

bool MapData::IsPositionPlayerAct(const glm::vec2& position) const {
    return IsWalkable(GamePosition2MapIndex(position))
           || IsPositionInteractive(position);
}

glm::ivec2 MapData::GetSize() const {
    return m_Size;
}

void MapData::SetSize(const glm::ivec2& size) {
    m_Size = size;
}

void MapData::SetHasEntity(const std::size_t position, const bool hasEntity) {
    m_HasEntity.at(position) = hasEntity;
}

glm::vec2 MapData::GetPlayerPosition() {
    return m_PlayerPosition;
}

void MapData::SetPlayerPosition(const glm::vec2& playerPosition) {
    m_PlayerPosition = playerPosition;
}

std::vector<std::shared_ptr<Tile>> MapData::GetUnsortedTiles() const {
    return m_TilesQueue;
}

float MapData::Heuristic(const glm::vec2& start, const glm::vec2& end) {
    return AStar::Heuristic(start, end);
}
}  // namespace Dungeon
