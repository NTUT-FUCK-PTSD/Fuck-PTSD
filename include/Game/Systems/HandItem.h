//
// Created by 陳世昂 on 2024/5/11.
//

#ifndef FUCK_PTSD_HIIS_H
#define FUCK_PTSD_HIIS_H

/* Handle-Item-Interaction-System*/

#include <iostream>
#include <memory>
#include "BlackChest.h"
#include "Item.h"
#include "Settings/Hash.h"
#include "Util/Logger.hpp"
#include "Warehouse/Throw.h"

namespace Game::Systems {
class HandItem {
public:
    HandItem(std::shared_ptr<Dungeon::Map> map, std::shared_ptr<Player> player)
        : m_DungeonMap(map),
          m_MainCharacter(player){

          };

    void DispatchByMI(
        std::shared_ptr<Dungeon::Item> equip,
        std::size_t                    nextPos
    ) {
        switch (HashConvert(equip->GetClassName())) {
        case "BlackChest"_hash: HandBlackChest(nextPos); break;
        case "Spear"_hash: HandSpear(nextPos); break;
        }
    };

private:
    void HandBlackChest(std::size_t nextPos) {
        const auto& test = std::static_pointer_cast<Game::Graphs::BlackChest>(
            m_DungeonMap->GetMapData()->GetItem(nextPos)
        );

        const auto& [a, b] = test->GetContent();
        m_MainCharacter->GetToolMod()->RemoveTool("WEAPON", "Spear");
        m_MainCharacter->GetToolMod()->AddTool(a, b);
        const auto& _throw = std::make_shared<Game::Warehouse::Throw>(
            Config::IMAGE_DAGGER_PATH
        );

        m_MainCharacter->GetToolMod()->AddTool(_throw, "THROW", "Dagger");

        m_DungeonMap->RemoveItem(nextPos);
    }

    void HandSpear(std::size_t nextPos) {
        m_DungeonMap->RemoveItem(nextPos);
        m_MainCharacter->GetToolMod()->DisappearTool(true, "WEAPON", "Spear");
    }

    std::shared_ptr<Dungeon::Map> m_DungeonMap;
    std::shared_ptr<Player>       m_MainCharacter;
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HIIS_H
