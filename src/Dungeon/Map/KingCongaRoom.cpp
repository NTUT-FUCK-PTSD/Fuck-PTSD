#include "CSnake.h"
#include "Dungeon/Map.h"

#include <memory>
#include "glm/ext/vector_int2.hpp"

#include "Dungeon/Enemies/Zombie.h"
#include "Dungeon/EnemyFactory.h"
#include "Enemies/KingConga.h"
#include "Music/Player.h"
#include "Music/Tempo.h"
#include "Settings/Window.hpp"
#include "Util/Image.hpp"

namespace Dungeon {
void Map::KingConga() {
    bool loadLevel = LoadLevel(m_BossLevel, 1, m_MapData->GetPlayer());
    if (loadLevel) {
        Music::Player::PlayMusic(ASSETS_DIR "/music/boss_1.ogg", true);
        Music::Tempo::ReadTempoFile(ASSETS_DIR "/music/boss_1.txt");
    } else {
        return;
    }

    // Add King Conga
    auto gamePos = glm::ivec2(0, -17);
    auto mapIndex = GamePostion2MapIndex(gamePos);
    auto kingConga = std::make_shared<Enemies::KingConga>(
        s_Enemy{gamePos.x, gamePos.y, 407, 0, 0},
        m_MapData
    );
    auto kingCongaBridge = kingConga->GetBridge();
    m_MapData->AddEnemy(mapIndex, kingConga);
    m_EnemyHead->AddChild(kingConga);
    auto chairImg = std::make_shared<Util::Image>(
        ASSETS_DIR "/entities/king_conga_throne.png"
    );
    // Add Boss Chair
    auto chairObj = std::make_shared<GameElement>();
    chairObj->SetDrawable(chairImg);
    chairObj->SetScale(Window::GetScale());
    chairObj->SetPosition(
        ToolBoxs::GamePostoPos({gamePos.x, gamePos.y}) + glm::vec2(3, 0)
    );
    chairObj->SetZIndex(-16.5);
    chairObj->SetVisible(false);
    kingConga->AddChild(chairObj);
    // Add Left Ghost
    gamePos = glm::ivec2(-7, -17);
    mapIndex = GamePostion2MapIndex(gamePos);
    auto ghostLeft = EnemyFactory::CreateEnemy(
        s_Enemy{gamePos.x, gamePos.y, 11, 0, 0},
        m_MapData
    );
    m_MapData->AddEnemy(mapIndex, ghostLeft);
    m_EnemyHead->AddChild(ghostLeft);
    // Add Right Ghost
    gamePos = glm::ivec2(7, -17);
    mapIndex = GamePostion2MapIndex(gamePos);
    auto ghostRight = EnemyFactory::CreateEnemy(
        s_Enemy{gamePos.x, gamePos.y, 11, 0, 0},
        m_MapData
    );
    m_MapData->AddEnemy(mapIndex, ghostRight);
    m_EnemyHead->AddChild(ghostRight);
    // Add Left Bat
    gamePos = glm::ivec2(-5, -11);
    mapIndex = GamePostion2MapIndex(gamePos);
    auto batLeft = EnemyFactory::CreateEnemy(
        s_Enemy{gamePos.x, gamePos.y, 6, 0, 0},
        m_MapData
    );
    m_MapData->AddEnemy(mapIndex, batLeft);
    m_EnemyHead->AddChild(batLeft);
    // Add Right Bat
    gamePos = glm::ivec2(5, -11);
    mapIndex = GamePostion2MapIndex(gamePos);
    auto batRight = EnemyFactory::CreateEnemy(
        s_Enemy{gamePos.x, gamePos.y, 6, 0, 0},
        m_MapData
    );
    m_MapData->AddEnemy(mapIndex, batRight);
    m_EnemyHead->AddChild(batRight);
    // Add Left Snake Zombie
    std::vector<glm::ivec2> gamePosSZLeft = {
      {-3, -15},
      {-4, -15},
      {-5, -15},
      {-6, -15},
      {-6, -16},
      {-5, -16},
      {-4, -16},
      {-3, -16}
    };
    std::size_t counter = 0;

    std::shared_ptr<Enemies::Zombie> previousZombie = nullptr;
    for (auto& pos : gamePosSZLeft) {
        mapIndex = GamePostion2MapIndex(pos);
        auto zombie = std::make_shared<Enemies::Zombie>(
            s_Enemy{pos.x, pos.y, 10, 0, 0},
            m_MapData
        );
        zombie->SnakeVersion(counter++, false);
        if (previousZombie != nullptr) {
            zombie->SetPreviousSnake(previousZombie->GetSnake());
            previousZombie->SetNextSnake(zombie->GetSnake());
        }
        m_MapData->AddEnemy(mapIndex, zombie);
        m_EnemyHead->AddChild(zombie);
        previousZombie = zombie;
    }
    previousZombie->SetBridge(kingCongaBridge);
    // Add Right Snake Zombie
    std::vector<glm::ivec2> gamePosSZRight = {
      {3, -15},
      {4, -15},
      {5, -15},
      {6, -15},
      {6, -16},
      {5, -16},
      {4, -16},
      {3, -16}
    };

    counter = 0;
    previousZombie = nullptr;
    for (auto& pos : gamePosSZRight) {
        mapIndex = GamePostion2MapIndex(pos);
        auto zombie = std::make_shared<Enemies::Zombie>(
            s_Enemy{pos.x, pos.y, 10, 0, 0},
            m_MapData
        );
        zombie->SnakeVersion(counter++, true);
        if (previousZombie != nullptr) {
            zombie->SetPreviousSnake(previousZombie->GetSnake());
            previousZombie->SetNextSnake(zombie->GetSnake());
        }
        m_MapData->AddEnemy(mapIndex, zombie);
        m_EnemyHead->AddChild(zombie);
        previousZombie = zombie;
    }
    previousZombie->SetBridge(kingCongaBridge);
    m_BossRoom = 1;
}

}  // namespace Dungeon
