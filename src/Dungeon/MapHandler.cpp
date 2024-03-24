#include "Dungeon/MapHandler.h"

namespace Dungeon {
MapHandler::MapHandler(const std::shared_ptr<Map> &map)
    : m_Map(map) {}

void MapHandler::Draw(const Util::Transform &transform, const float zIndex) {
    if (m_Map) {
        // Here can call m_Map functions
    }
}

} // namespace Dungeon
