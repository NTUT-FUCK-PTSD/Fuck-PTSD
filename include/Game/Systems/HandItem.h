//
// Created by 陳世昂 on 2024/5/11.
//

#ifndef FUCK_PTSD_HIIS_H
#define FUCK_PTSD_HIIS_H

/* Handle-Item-Interaction-System*/

#include <iostream>
#include <memory>
#include "Black_Chest.h"
#include "Item.h"
#include "Util/Logger.hpp"

namespace Game::Systems {
class HandItem {
public:
    explicit HandItem() = default;

    void DispatchByMI(std::shared_ptr<Dungeon::Item> equip) {
        LOG_INFO(typeid(std::shared_ptr<Graphs::BlackChest>) == typeid(equip));

        if (typeid(equip) == typeid(std::shared_ptr<Graphs::BlackChest>)) {
            LOG_INFO("true");
        }
    };
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HIIS_H
