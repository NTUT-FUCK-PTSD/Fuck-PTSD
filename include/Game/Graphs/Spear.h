//
// Created by adven on 2024/5/10.
//

#ifndef FUCK_PTSD_SPEAR_H
#define FUCK_PTSD_SPEAR_H

#include "Dungeon/Item.h"

namespace Game::Graphs {
class Spear final : public Dungeon::Item {
public:
    explicit Spear() = default;
    virtual ~Spear() = default;

    std::string GetClassName() override { return "Spear"; }
};
}  // namespace Game::Graphs

#endif  // FUCK_PTSD_SPEAR_H
