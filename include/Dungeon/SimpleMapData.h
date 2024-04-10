#ifndef SIMPLE_MAP_DATA_H
#define SIMPLE_MAP_DATA_H

#include "Dungeon/Tile.h"
#include <deque>
#include <vector>

namespace Dungeon {
class SimpleMapData {
public:
    SimpleMapData(const glm::ivec2 &levelIndexMin,
                  const glm::ivec2 &levelIndexMax, const glm::ivec2 &size);

    virtual ~SimpleMapData() = default;

    [[nodiscard]] glm::ivec2 GetLevelIndexMax() const;
    [[nodiscard]] glm::ivec2 GetLevelIndexMin() const;
    [[nodiscard]] glm::ivec2 GetSize() const;
    [[nodiscard]] glm::vec2 GetPlayerPosition() const;

    void SetLevelIndexMax(const glm::ivec2 &levelIndexMax);
    void SetLevelIndexMin(const glm::ivec2 &levelIndexMin);
    void SetSize(const glm::ivec2 &size);
    void SetPlayerPosition(const glm::vec2 &playerPosition);

    [[nodiscard]] std::size_t
    GamePosition2MapIndex(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionValid(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsHasEntity(const size_t &position) const;
    [[nodiscard]] bool IsWalkable(const size_t &position) const;
    [[nodiscard]] bool IsPositionWalkable(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionDoor(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionWall(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionCoin(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionDiamond(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionHeart(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionTool(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionPlayer(const glm::vec2 &position) const;
    [[nodiscard]] bool IsPositionInteractive(const glm::ivec2 &position) const;
    [[nodiscard]] bool IsPositionPlayerAct(const glm::vec2 &position) const;

    void AddTile(const size_t &position, const std::shared_ptr<Tile> &tile);
    void RemoveTile(const size_t &position, const std::shared_ptr<Tile> &tile);
    void PopBackTile(const size_t &position);
    [[nodiscard]] bool IsTilesEmpty(const size_t &position) const;
    [[nodiscard]] std::vector<std::shared_ptr<Tile>>
    GetTiles(const size_t &position) const;
    [[nodiscard]] std::shared_ptr<Tile>
    GetTileBack(const size_t &position) const;
    void SetHasEntity(const size_t &position, const bool &hasEntity);

    std::deque<std::shared_ptr<Tile>> GetTilesQueue() const;

private:
    glm::ivec2 m_LevelIndexMin;
    glm::ivec2 m_LevelIndexMax;
    glm::ivec2 m_Size;
    std::vector<bool> m_HasEntity;
    std::vector<std::vector<std::shared_ptr<Tile>>> m_Tiles;
    std::deque<std::shared_ptr<Tile>> m_TilesQueue;

    glm::vec2 m_PlayerPosition;
};
} // namespace Dungeon

#endif // SIMPLE_MAP_DATA_H
