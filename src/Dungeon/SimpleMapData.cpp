#include "Dungeon/AStar.h"

#include "Dungeon/SimpleMapData.h"

namespace Dungeon {
SimpleMapData::SimpleMapData(const glm::ivec2 &levelIndexMin,
                             const glm::ivec2 &levelIndexMax,
                             const glm::ivec2 &size)
    : m_LevelIndexMin(levelIndexMin),
      m_LevelIndexMax(levelIndexMax),
      m_Size(size) {
    m_Tiles.resize(GetSize().x * GetSize().y);
    m_HasEntity.resize(GetSize().x * GetSize().y, false);
}

void SimpleMapData::AddTile(const std::size_t position,
                            const std::shared_ptr<Tile> tile) {
    m_Tiles.at(position).emplace_back(tile);
    m_TilesQueue.emplace_back(tile);
}

void SimpleMapData::RemoveTile(const std::size_t position,
                               const std::shared_ptr<Tile> tile) {
    m_Tiles.at(position).erase(std::remove(m_Tiles.at(position).begin(),
                                           m_Tiles.at(position).end(), tile),
                               m_Tiles.at(position).end());
    m_TilesQueue.erase(
        std::remove(m_TilesQueue.begin(), m_TilesQueue.end(), tile),
        m_TilesQueue.end());
}

void SimpleMapData::ClearTiles() {
    m_Tiles.clear();
    m_Tiles.resize(GetSize().x * GetSize().y);
    m_TilesQueue.clear();
}

void SimpleMapData::PopBackTile(const std::size_t position) {
    m_TilesQueue.erase(std::remove(m_TilesQueue.begin(), m_TilesQueue.end(),
                                   m_Tiles.at(position).back()),
                       m_TilesQueue.end());
    m_Tiles.at(position).pop_back();
}

bool SimpleMapData::IsTilesEmpty(const std::size_t position) const {
    return m_Tiles.at(position).empty();
}

std::vector<std::shared_ptr<Tile>>
SimpleMapData::GetTiles(const std::size_t position) const {
    return m_Tiles.at(position);
}

std::shared_ptr<Tile>
SimpleMapData::GetTileBack(const std::size_t position) const {
    return m_Tiles.at(position).back();
}

glm::ivec2 SimpleMapData::GetLevelIndexMax() const {
    return m_LevelIndexMax;
}

glm::ivec2 SimpleMapData::GetLevelIndexMin() const {
    return m_LevelIndexMin;
}

void SimpleMapData::SetLevelIndexMax(const glm::ivec2 &levelIndexMax) {
    m_LevelIndexMax = levelIndexMax;
}

void SimpleMapData::SetLevelIndexMin(const glm::ivec2 &levelIndexMin) {
    m_LevelIndexMin = levelIndexMin;
}

std::size_t
SimpleMapData::GamePosition2MapIndex(const glm::ivec2 &position) const {
    return (position.x - GetLevelIndexMin().x + 1) +
           (position.y - GetLevelIndexMin().y + 1) * m_Size.x;
}

bool SimpleMapData::IsPositionValid(const glm::ivec2 &position) const {
    return position.x >= GetLevelIndexMin().x &&
           position.x <= GetLevelIndexMax().x &&
           position.y >= GetLevelIndexMin().y &&
           position.y <= GetLevelIndexMax().y;
}

bool SimpleMapData::IsHasEntity(const std::size_t position) const {
    return m_HasEntity.at(position);
}

bool SimpleMapData::IsWalkable(const std::size_t position) const {
    return !IsTilesEmpty(position) && !GetTileBack(position)->IsWall() &&
           !GetTileBack(position)->IsDoor() && !m_HasEntity.at(position);
}

bool SimpleMapData::IsPositionWalkable(const glm::ivec2 &position) const {
    return IsPositionValid(position) &&
           IsWalkable(GamePosition2MapIndex(position));
}

bool SimpleMapData::IsPositionDoor(const glm::ivec2 &position) const {
    return IsPositionValid(position) &&
           !IsTilesEmpty(GamePosition2MapIndex(position)) &&
           GetTileBack(GamePosition2MapIndex(position))->IsDoor();
}

bool SimpleMapData::IsPositionWall(const glm::ivec2 &position) const {
    return IsPositionValid(position) &&
           !IsTilesEmpty(GamePosition2MapIndex(position)) &&
           GetTileBack(GamePosition2MapIndex(position))->IsWall();
}

bool SimpleMapData::IsPositionCoin(
    [[maybe_unused]] const glm::ivec2 &position) const {
    return false;
}

bool SimpleMapData::IsPositionDiamond(
    [[maybe_unused]] const glm::ivec2 &position) const {
    return false;
}

bool SimpleMapData::IsPositionHeart(
    [[maybe_unused]] const glm::ivec2 &position) const {
    return false;
}

bool SimpleMapData::IsPositionTool(
    [[maybe_unused]] const glm::ivec2 &position) const {
    return false;
}

bool SimpleMapData::IsPositionPlayer(const glm::vec2 &position) const {
    return position == m_PlayerPosition;
}

bool SimpleMapData::IsPositionInteractive(const glm::ivec2 &position) const {
    return IsPositionValid(position) &&
           !IsTilesEmpty(GamePosition2MapIndex(position)) &&
           (IsPositionDoor(position) || IsPositionWall(position) ||
            IsHasEntity(GamePosition2MapIndex(position)) ||
            IsPositionPlayer(position) || IsPositionCoin(position) ||
            IsPositionDiamond(position) || IsPositionHeart(position) ||
            IsPositionTool(position));
}

bool SimpleMapData::IsPositionPlayerAct(const glm::vec2 &position) const {
    return IsWalkable(GamePosition2MapIndex(position)) ||
           IsPositionInteractive(position);
}

glm::ivec2 SimpleMapData::GetSize() const {
    return m_Size;
}

void SimpleMapData::SetSize(const glm::ivec2 &size) {
    m_Size = size;
}

void SimpleMapData::SetHasEntity(const std::size_t position,
                                 const bool &hasEntity) {
    m_HasEntity.at(position) = hasEntity;
}

glm::vec2 SimpleMapData::GetPlayerPosition() {
    return m_PlayerPosition;
}

void SimpleMapData::SetPlayerPosition(const glm::vec2 &playerPosition) {
    m_PlayerPosition = playerPosition;
}

std::vector<std::shared_ptr<Tile>> SimpleMapData::GetTilesQueue() const {
    return m_TilesQueue;
}

float SimpleMapData::Heuristic(const glm::vec2 &start, const glm::vec2 &end) {
    return AStar::Heuristic(start, end);
}
} // namespace Dungeon

glm::vec2 Dungeon::SimpleMapData::m_PlayerPosition = {0, 0};
