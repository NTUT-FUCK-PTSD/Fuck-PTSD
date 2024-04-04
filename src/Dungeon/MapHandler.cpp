#include "Dungeon/MapHandler.h"

namespace Dungeon {
MapHandler::MapHandler(const std::shared_ptr<Map> &map)
    : m_Map(map) {}

void MapHandler::Draw(const Core::Matrices &data) {
    if (m_Map) {
        (void)data;
        // Here can call m_Map functions
        m_Map->Update();
    }
}

} // namespace Dungeon
