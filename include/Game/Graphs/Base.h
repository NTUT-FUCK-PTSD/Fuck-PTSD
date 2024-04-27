#ifndef FUCK_PTSD_GAME_GRPHS_BASE_H
#define FUCK_PTSD_GAME_GRPHS_BASE_H

#include "Dungeon/Map.h"
#include "Util/GameObject.hpp"
#include "glm/vec2.hpp"

namespace Game {
namespace Graphs {
class IBase : public Util::GameObject {
public:
    std::size_t  MI = 0;
    virtual void Update(Dungeon::Map* dungeonMap) = 0;
};
}  // namespace Graphs
}  // namespace Game

#endif  // FUCK_PTSD_GAME_GRPHS_BASE_H
