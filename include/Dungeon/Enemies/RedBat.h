#ifndef REDBAT_H
#define REDBAT_H

#include "Dungeon/Enemies/Bat.h"

namespace Dungeon {
namespace Enemies {
class RedBat final : public Bat {
public:
    RedBat(const s_Enemy &u_Enemy,
           const std::shared_ptr<SimpleMapData> &simpleMapData);
};
} // namespace Enemies
} // namespace Dungeon

#endif // REDBAT_H
