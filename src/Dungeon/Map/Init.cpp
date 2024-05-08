#include "Dungeon/Map.h"

#include "Dungeon_config.h"
#include "Event/Event.h"

namespace Dungeon {
Map::Map(
    const std::shared_ptr<Camera> camera,
    const std::string&            path,
    const std::size_t             levelNum
)
    : m_Camera(camera),
      m_Event(Event::EventQueue) {
    // ZIndex 98~100 is for UI
    m_ZIndex = 98;
    m_Transform.scale = {DUNGEON_SCALE + 1, DUNGEON_SCALE + 1};
    m_Transform.translation = {0, 0};
    m_Level = std::make_unique<Level>(path);
    m_Available = LoadLevel(levelNum);

    Dungeon::config::PTR_IMAGE_FULL_HEART_SM = std::make_shared<Util::Image>(
        Dungeon::config::IMAGE_FULL_HEART_SM.data()
    );

    Dungeon::config::PTR_IMAGE_EMPTY_HEART_SM = std::make_shared<Util::Image>(
        Dungeon::config::IMAGE_EMPTY_HEART_SM.data()
    );

    // Add enemy testing
    // auto mapIndex = GamePostion2MapIndex({1, 1});
    // auto enemy = EnemyFactory::CreateEnemy(s_Enemy{1, 1, 11, 0, 0},
    // m_MapData); m_MapData->AddEnemy(mapIndex, enemy);
    // m_Children.push_back(enemy);

    InitEvent();
}

Map::~Map() {
    Event::EventQueue.dispatch(this, EventArgs(EventType::ResetMap));
}

bool Map::LoadLevel(const std::size_t levelNum) {
    Event::EventQueue.dispatch(this, EventArgs(EventType::ResetMap));

    if (!m_Level->LoadLevel(levelNum)) {
        m_Available = false;
        return false;
    }
    m_LevelNum = levelNum;

    m_Size = m_Level->GetLevelIndexMax() - m_Level->GetLevelIndexMin()
             + 3;  // add 3 for the border
    m_MapData = std::make_shared<MapData>(
        m_Level->GetLevelIndexMin(),
        m_Level->GetLevelIndexMax(),
        m_Size
    );

    LoadTile();
    LoadEnemy();
    if (m_MiniMap) {
        m_Camera->RemoveUIChild(m_MiniMap);
        m_MiniMap.reset();
    }
    m_MiniMap = std::make_shared<MiniMap>(m_MapData);
    m_Camera->AddUIChild(m_MiniMap);

    m_ShadowRenderDP.clear();
    m_ShadowRenderDP.resize(m_Size.x * m_Size.y, false);
    CameraUpdate();
    m_MiniMap->Update();
    return true;
}
}  // namespace Dungeon
