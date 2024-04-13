#include "Dungeon/MapHandler.h"

namespace Dungeon {
MapHandler::MapHandler(const std::shared_ptr<Map> map)
    : m_Map(map) {
    m_Image =
        std::make_shared<Util::Image>(ASSETS_DIR "/gui/TEMP_overlay_red.png");
}

void MapHandler::Draw(const Core::Matrices &data) {
    if (m_Map) {
        // Here can call m_Map functions
        m_Map->Update();
        if (m_Map->GetOverlayRed()) {
            m_Image->Draw(data);
        }
    }
}

} // namespace Dungeon
