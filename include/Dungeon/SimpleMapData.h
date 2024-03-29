#ifndef SIMPLE_MAP_DATA_H
#define SIMPLE_MAP_DATA_H

#include "Dungeon/Tile.h"
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

    void SetLevelIndexMax(const glm::ivec2 &levelIndexMax);
    void SetLevelIndexMin(const glm::ivec2 &levelIndexMin);
    void SetSize(const glm::ivec2 &size);

    size_t GamePostion2MapIndex(const glm::ivec2 &position) const;

    void AddTile(const size_t &position, const std::shared_ptr<Tile> &tile);
    void RemoveTile(const size_t &position, const std::shared_ptr<Tile> &tile);
    void PopbackTile(const size_t &position);
    bool IsTilesEmpty(const size_t &position) const;
    std::vector<std::shared_ptr<Tile>> GetTiles(const size_t &position) const;
    std::shared_ptr<Tile> GetTileBack(const size_t &position) const;

private:
    glm::ivec2 m_LevelIndexMin;
    glm::ivec2 m_LevelIndexMax;
    glm::ivec2 m_Size;
    std::vector<std::vector<std::shared_ptr<Tile>>> m_Tiles;
};
} // namespace Dungeon

#endif // SIMPLE_MAP_DATA_H
