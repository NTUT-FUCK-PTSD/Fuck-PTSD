#include <memory>
#include "Dungeon/Map.h"

#include "Dungeon/EnemyFactory.h"
#include "Dungeon_config.h"
#include "Event/Event.h"
#include "Settings/Window.hpp"

namespace Dungeon {
Map::Map(
    const std::shared_ptr<Camera> camera,
    const std::shared_ptr<Player> player,
    const std::string&            path,
    const std::size_t             levelNum
)
    : m_Camera(camera),
      m_Event(Event::EventQueue) {
    // ZIndex 98~100 is for UI
    m_ZIndex = 98;
    m_Transform.scale = {Window::Scale + 1, Window::Scale + 1};
    m_Transform.translation = {0, 0};
    m_Path = path;
    m_Level = std::make_shared<Level>(path);
    m_BossLevel =
        std::make_shared<Level>(ASSETS_DIR "/dungeon/boss_room.xml", 1);
    m_Available = LoadLevel(levelNum, player);
    AddChild(m_TileHead);
    AddChild(m_EnemyHead);
    AddChild(m_ItemHead);

    Dungeon::config::PTR_IMAGE_FULL_HEART_SM = std::make_shared<Util::Image>(
        Dungeon::config::IMAGE_FULL_HEART_SM.data()
    );

    Dungeon::config::PTR_IMAGE_EMPTY_HEART_SM = std::make_shared<Util::Image>(
        Dungeon::config::IMAGE_EMPTY_HEART_SM.data()
    );

    // Add enemy testing
    // auto gamePos = glm::ivec2(2, 2);
    // auto mapIndex = GamePostion2MapIndex(gamePos);
    // auto enemy = EnemyFactory::CreateEnemy(
    //     s_Enemy{gamePos.x, gamePos.y, 407, 0, 0},
    //     m_MapData
    // );
    // m_MapData->AddEnemy(mapIndex, enemy);
    // m_EnemyHead->AddChild(enemy);

    InitEvent();
}

Map::~Map() {
    Event::EventQueue.dispatch(this, EventArgs(EventType::ResetMap));
}

bool Map::LoadLevel(
    const std::size_t             levelNum,
    const std::shared_ptr<Player> player
) {
    return LoadLevel(m_Level, levelNum, player);
}

bool Map::LoadLevel(
    const std::shared_ptr<Level>  level,
    const std::size_t             levelNum,
    const std::shared_ptr<Player> player
) {
    if (static_cast<int>(levelNum) > level->GetNumLevels()) {
        KingConga();
        return false;
    }
    Event::EventQueue.dispatch(this, EventArgs(EventType::ResetMap));

    if (!level->LoadLevel(levelNum)) {
        m_Available = false;
        return false;
    }
    m_LevelNum = levelNum;

    m_Size = level->GetLevelIndexMax() - level->GetLevelIndexMin() + 3;
    m_MapData = std::make_shared<MapData>(
        level->GetLevelIndexMin(),
        level->GetLevelIndexMax(),
        m_Size,
        player
    );

    LoadTile(level);
    LoadEnemy(level);
    m_MiniMap = std::make_shared<MiniMap>(m_MapData);
    m_Camera->AddUIChild(m_MiniMap);

    m_ShadowRenderDP.clear();
    m_ShadowRenderDP.resize(m_Size.x * m_Size.y, false);
    CameraUpdate();
    m_MiniMap->Update();
    m_Available = true;
    return true;
}
}  // namespace Dungeon
