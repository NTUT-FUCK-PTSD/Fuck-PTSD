#ifndef MAP_H
#define MAP_H

#include "Util/GameObject.hpp"

#include "Camera.h"
#include "Dungeon/Enemy.h"
#include "Dungeon/Level.h"
#include "Dungeon/MapData.h"
#include "Dungeon/MiniMap.h"
#include "Player/Player.h"

namespace Dungeon {
class Map final : public Util::GameObject {
public:
    Map(const std::shared_ptr<Camera> camera,
        const std::shared_ptr<Player> mainCharacter,
        const std::string&            path,
        const std::size_t             levelNum = 1);
    ~Map();

    bool        IsAvailable() { return m_Available; }
    bool        LoadLevel(const std::size_t levelNum);
    std::size_t GetLevelNum() const;

    std::size_t GamePostion2MapIndex(const glm::ivec2& position) const;

    std::shared_ptr<MapData> GetMapData() const;

    void RemoveEnemy(const std::size_t position);
    void RemoveWall(const std::size_t position);
    void OpenDoor(const std::size_t position);

    void CameraUpdate();
    void PlayerTrigger();
    void TempoTrigger(const std::size_t index);

    void Update();

    bool IsOverlayRed() const { return m_OverlayRed; }

private:
    bool m_Available;
    void LoadTile();
    void LoadEnemy();

    void TempoUpdate(bool isPlayer);

    std::vector<glm::vec2> m_EnemyMove = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    std::vector<glm::ivec2> m_Direction =
        {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    const std::size_t ALLOW_EXTRA_DRAW = 4;
    bool              CheckShowPosition(
                     const glm::vec2& position1,
                     const glm::vec2& position2
                 );
    bool isVaildPosition(const glm::ivec2& position);
    bool isVaildMove(const glm::ivec2& position);
    // use reference to avoid copy
    void EnemyAttackHandle(const std::shared_ptr<Enemy>& enemy);
    bool CanPlayerSeePosition(const glm::vec2& position);

    void DoorUpdate(std::size_t i, std::size_t j);

    const std::size_t        HalfColNumber = DUNGEON_COL_NUMBER / 2;
    const std::size_t        HalfRowNumber = DUNGEON_ROW_NUMBER / 2;
    std::unique_ptr<Level>   m_Level;
    std::size_t              m_LevelNum;
    glm::ivec2               m_Size;
    std::shared_ptr<MapData> m_MapData;  // Use map index to store MapDate
    std::shared_ptr<Camera>  m_Camera;
    std::shared_ptr<Player>  m_MainCharacter;

    bool          m_TempoAttack = false;
    bool          m_OverlayRed = false;
    unsigned long m_OverlayRedTime = 0;

    std::vector<bool> m_ShadowRenderDP;

    std::shared_ptr<MiniMap> m_MiniMap;

    std::size_t m_TempoIndex = 0;
};

}  // namespace Dungeon
#endif  // MAP_H
