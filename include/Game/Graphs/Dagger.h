#ifndef DAGGER_H
#define DAGGER_H
#include "Dungeon/Item.h"
#include "Settings/Helper.hpp"

#include "Util/Logger.hpp"

namespace Game {
namespace Graphs {
class Dagger final : public Dungeon::Item {
public:
    explicit Dagger() {}

    virtual ~Dagger() override = default;

    std::string GetClassName() override { return "Dagger"; }
};
}  // namespace Graphs
}  // namespace Game

#endif  // DAGGER_H
