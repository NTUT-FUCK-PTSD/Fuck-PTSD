#ifndef MAP_DATA_H
#define MAP_DATA_H

#include <memory>
#include <vector>

#include "Dungeon/EMfwd.h"
#include "Dungeon/Item.h"
#include "Dungeon/Tile.h"
#include "Enemy.h"
#include "Game/Player.h"

namespace Dungeon {
class MapData final {
public:
    MapData(
        const glm::vec2&              levelIndexMin,
        const glm::vec2&              levelIndexMax,
        const glm::vec2&              size,
        const std::shared_ptr<Player> player
    );

    // tile
    void AddTile(const std::size_t position, const std::shared_ptr<Tile> tile);
    void RemoveTile(const std::size_t position);
    void ClearTiles();
    std::vector<std::shared_ptr<Tile>> GetTiles() const;
    bool                  IsTileEmpty(const std::size_t position) const;
    std::shared_ptr<Tile> GetTile(const std::size_t position) const;
    std::vector<std::shared_ptr<Tile>> GetUnsortedTiles() const;

    // enemy
    void AddEnemy(
        const std::size_t            position,
        const std::shared_ptr<Enemy> enemy
    );
    void RemoveEnemy(const std::size_t position);
    void MoveEnemy(const std::size_t src, const std::size_t dest);
    void ClearEnemies();
    std::vector<std::shared_ptr<Enemy>> GetEnemies() const;
    std::shared_ptr<Enemy> GetEnemy(const std::size_t position) const;
    std::shared_ptr<Enemy> GetBoss() const;
    std::vector<std::shared_ptr<Enemy>> GetEnemyQueue() const;
    std::vector<std::shared_ptr<Enemy>> GetUnsortedEnemies() const;
    bool IsEnemyEmpty(const std::size_t position) const;

    // item
    void AddItem(const std::size_t position, const std::shared_ptr<Item> item);
    void RemoveItem(const std::size_t position);
    void ClearItems();
    std::shared_ptr<Item> GetItem(const std::size_t position) const;
    bool                  IsItemEmpty(const std::size_t position) const;

    glm::ivec2 GetLevelIndexMax() const;
    glm::ivec2 GetLevelIndexMin() const;
    glm::ivec2 GetSize() const;
    glm::vec2  GetPlayerPosition() const;

    void SetLevelIndexMax(const glm::ivec2& levelIndexMax);
    void SetLevelIndexMin(const glm::ivec2& levelIndexMin);
    void SetSize(const glm::ivec2& size);

    std::size_t GamePosition2MapIndex(const glm::ivec2& position) const;

    bool IsPositionValid(const glm::ivec2& position) const;
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
    bool IsBossDead() const;

    float Heuristic(const glm::vec2& start, const glm::vec2& end);
    std::shared_ptr<Player> GetPlayer() const;

private:
    static bool EnemyCompare(
        std::shared_ptr<Enemy>& lhs,
        std::shared_ptr<Enemy>& rhs
    );

    glm::ivec2 m_LevelIndexMin;
    glm::ivec2 m_LevelIndexMax;
    glm::ivec2 m_Size;

    std::vector<std::shared_ptr<Tile>>  m_Tiles;
    std::vector<std::shared_ptr<Tile>>  m_TilesQueue;
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::vector<std::shared_ptr<Enemy>> m_EnemyQueue;
    std::vector<std::shared_ptr<Item>>  m_Items;

    glm::vec2 m_PlayerPosition = {0.0f, 0.0f};

    std::shared_ptr<Enemy> m_Boss = nullptr;
    std::shared_ptr<Player> m_Player;
};
}  // namespace Dungeon

#endif  // MAP_DATA_H
