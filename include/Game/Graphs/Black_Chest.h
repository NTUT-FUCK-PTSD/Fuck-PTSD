//
// Created by 陳世昂 on 2024/5/11.
//

#ifndef FUCK_PTSD_BLACK_CHEST_H
#define FUCK_PTSD_BLACK_CHEST_H

#include "Dungeon/Item.h"

namespace Game::Graphs {
class BlackChest : public Dungeon::Item {
public:
    explicit BlackChest() = default;
    virtual ~BlackChest() = default;
};
}  // namespace Game::Graphs

#endif  // FUCK_PTSD_BLACK_CHEST_H
