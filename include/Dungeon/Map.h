#ifndef MAP_H
#define MAP_H

#include <memory>

#include "Util/GameObject.hpp"

#include "Dungeon/Direction.h"
#include "Dungeon/Level.h"
#include "Dungeon/MapData.h"
#include "Dungeon/MiniMap.h"
#include "Event/Event.h"
#include "Event/Object.h"
#include "Game/Player.h"
#include "Settings/Camera.h"
#include "Settings/GameElement.h"

namespace Dungeon {
class Map final : public Object, public Util::GameObject {
public:
    Map(const std::shared_ptr<Camera> camera,
        const std::shared_ptr<Player> player,
        const std::string&            path,
        const std::size_t             levelNum = 1);
    ~Map();

    void InitEvent();

    bool IsAvailable() { return m_Available; }
    bool LoadLevel(
        const std::size_t             levelNum,
        const std::shared_ptr<Player> player
    );
    bool LoadLevel(
        const std::shared_ptr<Level>  level,
        const std::size_t             levelNum,
        const std::shared_ptr<Player> player
    );
    std::size_t GetLevelNum() const;

    std::size_t GamePostion2MapIndex(const glm::ivec2& position) const;
    glm::ivec2  MapIndex2GamePosition(const std::size_t index) const;

    std::shared_ptr<MapData> GetMapData() const;

    void RemoveEnemy(const std::size_t position);
    void RemoveWall(const std::size_t position);
    void OpenDoor(const std::size_t position);

    void CameraUpdate();
    void PlayerTrigger();
    void TempoTrigger(const std::size_t index);

    void Update();

    bool IsOverlayRed() const { return m_OverlayRed; }

    glm::ivec2 GetSize() { return m_Size; }
    // glm::ivec2 GetLevelIndexMin() { return m_Level->GetLevelIndexMin(); }
    // glm::ivec2 GetLevelIndexMax() { return m_Level->GetLevelIndexMax(); }

    void AddItem(const std::size_t position, const std::shared_ptr<Item> item);
    void RemoveItem(const std::size_t position);

    void        KingConga();
    std::size_t GetBossRoomValue() const { return m_BossRoom; }

    void NoBeat() { m_NoBeat = true; }

private:
    bool m_Available;
    void LoadTile(std::shared_ptr<Level> level);
    void LoadEnemy(std::shared_ptr<Level> level);
    void LoadItem();  // TODO

    void TempoUpdate(bool isPlayer);

    std::vector<glm::vec2> m_EnemyMove = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    std::vector<glm::ivec2> m_Direction = {
      RIGHT,
      LEFT,
      BOTTOM,
      TOP,
      BOTTOM_RIGHT,
      TOP_RIGHT,
      BOTTOM_LEFT,
      TOP_LEFT
    };

    const std::size_t ALLOW_EXTRA_DRAW = 4;
    bool              CheckShowPosition(
                     const glm::vec2& position1,
                     const glm::vec2& position2
                 );
    bool CanPlayerSeePosition(const glm::vec2& position);

    void DoorUpdate(std::size_t i, std::size_t j);

    static glm::ivec2      m_Size;
    std::size_t            m_LevelNum;
    std::shared_ptr<Level> m_Level;
    std::shared_ptr<Level> m_BossLevel;
    std::string            m_Path;

    std::shared_ptr<MapData> m_MapData;  // Use map index to store MapDate
    std::shared_ptr<Camera>  m_Camera;

    bool          m_OverlayRed = false;
    unsigned long m_OverlayRedTime = 0;

    std::vector<bool> m_ShadowRenderDP;

    std::shared_ptr<MiniMap> m_MiniMap;

    std::size_t m_TempoIndex = 0;

    Event::Remover m_Event;

    std::shared_ptr<GameElement> m_TileHead = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_EnemyHead = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_ItemHead = std::make_shared<GameElement>();

    std::size_t m_CoinMultiple = 0;
    std::size_t m_BossRoom = 0;
    bool        m_NoBeat = false;
};

}  // namespace Dungeon
#endif  // MAP_H
