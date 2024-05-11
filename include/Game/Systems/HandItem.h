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
    explicit HandItem(
        const std::shared_ptr<Dungeon::Map>& map,
        const std::shared_ptr<Player>&       player
    );

    void DispatchByMI(
        const std::shared_ptr<Dungeon::Item>& equip,
        std::size_t                           nextPos
    );

private:
    void BlackChest(std::size_t nextPos);
    void Spear(std::size_t nextPos);
    void Dagger(std::size_t nextPos);
    void Food_1(std::size_t nextPos);
    void Food_2(std::size_t nextPos);

    std::shared_ptr<Dungeon::Map> m_DungeonMap;
    std::shared_ptr<Player>       m_MainCharacter;
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HIIS_H
