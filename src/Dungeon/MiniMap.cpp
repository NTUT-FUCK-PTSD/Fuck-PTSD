#include "Dungeon/MiniMap.h"

namespace Dungeon {
MiniMap::MiniMap(std::shared_ptr<MapData> mapData)
    : m_MapData(mapData) {
    std::size_t mapIndex = 0;
    for (int i = 0; i < m_MapData->GetSize().y; i++) {
        for (int j = 0; j < m_MapData->GetSize().x; j++) {
            mapIndex = j + i * m_MapData->GetSize().x;
            m_ColorCubes.push_back(std::make_shared<ColorCube>());
            m_Children.push_back(
                std::make_shared<Util::GameObject>(m_ColorCubes.back(), 100));
            m_Children[mapIndex]->SetVisible(true);
            m_Children[mapIndex]->m_Transform.scale = {DUNGEON_SCALE,
                                                       DUNGEON_SCALE};
            m_Children[mapIndex]->m_Transform.translation = {
                static_cast<int>(WINDOW_WIDTH) / 2 - DUNGEON_TILE_WIDTH -
                    (2 * (m_MapData->GetSize().x - (j + 1))) * DUNGEON_SCALE,
                -(static_cast<int>(WINDOW_HEIGHT) / 2) +
                    (52 * DUNGEON_SCALE + DUNGEON_TILE_WIDTH) +
                    (2 * (m_MapData->GetSize().y - (i + 1))) * DUNGEON_SCALE};
            if (!m_MapData->IsTilesEmpty(mapIndex)) {
                if (m_MapData->GetTileBack(mapIndex)->IsWall()) {
                    if (m_MapData->GetTileBack(mapIndex)->GetTile().type ==
                        102) {
                        m_ColorCubes[mapIndex]->SetColor(CubeColor::gray);
                    }
                    else {
                        m_ColorCubes[mapIndex]->SetColor(CubeColor::metrognome);
                    }
                }
                else if (m_MapData->GetTileBack(mapIndex)->IsDoor()) {
                    m_ColorCubes[mapIndex]->SetColor(CubeColor::green);
                }
                else {
                    m_ColorCubes[mapIndex]->SetColor(CubeColor::white);
                }
            }
            // m_ColorCubes[mapIndex]->SetColor(CubeColor::red);
        }
    }
}
void MiniMap::SetColor(const glm::vec2 &position, CubeColor color) {
    auto mapIndex = m_MapData->GamePosition2MapIndex(position);
    m_ColorCubes[mapIndex]->SetColor(color);
    m_Children[mapIndex]->SetVisible(true);
}
} // namespace Dungeon
