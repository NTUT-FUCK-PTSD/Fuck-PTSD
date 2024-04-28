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

    const auto& tile = m_DungeonMap->GetMapData()->GetTiles(posMI);
    const auto  tileBottom = tile.size() - 1;
    const auto& object = tile[tileBottom];

    baseType->m_Transform.translation = object->GetTransform().translation;
    baseType->MI = posMI;
    baseType->SetZIndex(object->GetZIndex() + 0.1f);
    object->AddChild(baseType);
    //        m_GameObject->AddChild(baseType);
}

// std::shared_ptr<Util::GameObject> Game::System::GetGameObject() {
//     return m_GameObject;
// }

void Game::System::Update() {
    if (m_IBaseList.empty()) {
        return;
    }

    for (std::size_t i = 0; i < m_IBaseList.size(); ++i) {
        auto& elem = m_IBaseList.at(i);

        elem->Update(m_DungeonMap);
    }
}

// std::shared_ptr<Util::GameObject> Game::System::m_GameObject = nullptr;
Dungeon::Map* Game::System::m_DungeonMap = nullptr;
std::vector<std::shared_ptr<Game::Graphs::IBase>> Game::System::m_IBaseList;
