#ifndef ITEM_H
#define ITEM_H

#include "Util/GameObject.hpp"

namespace Dungeon {
class Item : public Util::GameObject {
public:
    Item() = default;
    virtual ~Item() = default;

    virtual std::string GetClassName() = 0;

private:
};
}  // namespace Dungeon

#endif  // ITEM_H
