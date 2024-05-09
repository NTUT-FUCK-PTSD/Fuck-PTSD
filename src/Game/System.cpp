#include "Game/System.h"

#include <iostream>

#include "Settings/Helper.hpp"

void Game::System::Init(Dungeon::Map* dungeonMap) {
    m_DungeonMap = dungeonMap;
}

void Game::System::AddWeapon(
    std::shared_ptr<Game::Graphs::IBase> baseType,
    const std::size_t                    posMI
) {
    m_IBaseList.push_back(baseType);

    const auto& object = m_DungeonMap->GetMapData()->GetTile(posMI);
    LOG_INFO("{} {}", posMI, object->m_Filepath);
    if (!object) {
        return;
    }
    baseType->m_Transform.translation = object->GetTransform().translation;
    baseType->MI = posMI;
    baseType->SetZIndex(100);
    object->AddChild(baseType);
}

void Game::System::Update() {
    if (m_IBaseList.empty()) {
        return;
    }

    for (std::size_t i = 0; i < m_IBaseList.size(); ++i) {
        auto& elem = m_IBaseList.at(i);

        //        elem->Update(m_DungeonMap);
    }
}

// std::shared_ptr<Util::GameObject> Game::Systems::m_GameObject = nullptr;
Dungeon::Map* Game::System::m_DungeonMap = nullptr;
std::vector<std::shared_ptr<Game::Graphs::IBase>> Game::System::m_IBaseList;
