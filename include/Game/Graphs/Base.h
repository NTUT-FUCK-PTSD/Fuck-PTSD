#ifndef FUCK_PTSD_GAME_GRPHS_BASE_H
#define FUCK_PTSD_GAME_GRPHS_BASE_H

#include "Util/GameObject.hpp"

namespace Game {
namespace Graphs {
class IBase : public Util::GameObject {
public:
    virtual void Update() = 0;
};
}  // namespace Graphs
}  // namespace Game

#endif  // FUCK_PTSD_GAME_GRPHS_BASE_H
