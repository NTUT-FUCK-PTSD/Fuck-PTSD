#ifndef SIMPLE_MAP_DATA_H
#define SIMPLE_MAP_DATA_H

#include <vector>

#include "Dungeon/Tile.h"

namespace Dungeon {
class SimpleMapData {
public:
    SimpleMapData(
        const glm::ivec2& levelIndexMin,
        const glm::ivec2& levelIndexMax,
        const glm::ivec2& size
    );

    virtual ~SimpleMapData() = default;

    glm::ivec2 GetLevelIndexMax() const;
    glm::ivec2 GetLevelIndexMin() const;
    glm::ivec2 GetSize() const;
    glm::vec2  GetPlayerPosition();

    void SetLevelIndexMax(const glm::ivec2& levelIndexMax);
    void SetLevelIndexMin(const glm::ivec2& levelIndexMin);
    void SetSize(const glm::ivec2& size);
    void SetPlayerPosition(const glm::vec2& playerPosition);

    std::size_t GamePosition2MapIndex(const glm::ivec2& position) const;

    bool IsPositionValid(const glm::ivec2& position) const;
    bool IsHasEntity(const std::size_t position) const;
    bool IsWalkable(const std::size_t position) const;
    bool IsPositionWalkable(const glm::ivec2& position) const;
    bool IsPositionDoor(const glm::ivec2& position) const;
    bool IsPositionWall(const glm::ivec2& position) const;
    bool IsPositionCoin(const glm::ivec2& position) const;
    bool IsPositionDiamond(const glm::ivec2& position) const;
    bool IsPositionHeart(const glm::ivec2& position) const;
    bool IsPositionTool(const glm::ivec2& position) const;
    bool IsPositionPlayer(const glm::vec2& position) const;
    bool IsPositionInteractive(const glm::ivec2& position) const;
    bool IsPositionPlayerAct(const glm::vec2& position) const;

    void AddTile(const std::size_t position, const std::shared_ptr<Tile> tile);
    void RemoveTile(
        const std::size_t           position,
        const std::shared_ptr<Tile> tile
    );
    void ClearTiles();
    void PopBackTile(const std::size_t position);
    bool IsTilesEmpty(const std::size_t position) const;
    std::vector<std::shared_ptr<Tile>> GetTiles(const std::size_t position
    ) const;
    std::shared_ptr<Tile> GetTileBack(const std::size_t position) const;
    std::vector<std::shared_ptr<Tile>> GetTilesQueue() const;

    void SetHasEntity(const std::size_t position, const bool hasEntity);

    float Heuristic(const glm::vec2& start, const glm::vec2& end);

protected:
    std::vector<bool> m_HasEntity;

private:
    glm::ivec2                                      m_LevelIndexMin;
    glm::ivec2                                      m_LevelIndexMax;
    glm::ivec2                                      m_Size;
    std::vector<std::vector<std::shared_ptr<Tile>>> m_Tiles;
    std::vector<std::shared_ptr<Tile>>              m_TilesQueue;
    glm::vec2                                       m_PlayerPosition;
};
}  // namespace Dungeon

#endif  // SIMPLE_MAP_DATA_H
