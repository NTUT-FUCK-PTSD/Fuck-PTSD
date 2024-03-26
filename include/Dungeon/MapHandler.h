#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "Core/Drawable.hpp"

#include "Dungeon/Map.h"

namespace Dungeon {

class MapHandler : public Core::Drawable {
public:
    MapHandler(const std::shared_ptr<Map> &map);
    void Draw(const Util::Transform &transform, const float zIndex);
    glm::vec2 GetSize() const { return {0, 0}; };

private:
    const std::shared_ptr<Map> m_Map;
};

} // namespace Dungeon

#endif // MAP_HANDLER_H
