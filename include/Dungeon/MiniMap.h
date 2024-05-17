#ifndef MINIMAP_H
#define MINIMAP_H

#include "Util/GameObject.hpp"
#include "Util/Time.hpp"

#include "Dungeon/ColorCube.h"
#include "Dungeon/MapData.h"
#include "Event/Event.h"

namespace Dungeon {
class MiniMap : public Util::GameObject {
public:
    MiniMap(std::shared_ptr<MapData> mapData);
    ~MiniMap() = default;
    void SetColor(const glm::vec2& position, CubeColor color);
    void SetColor(const std::size_t position, CubeColor color);
    void SetVisible(const glm::vec2& position, bool visible);
    void SetVisible(const std::size_t position, bool visible);
    void SetScale(double scale);

    void Update();
    void UpdatePlayer();
    void UpdateCubeColor(const std::size_t mapIndex);

private:
    void BuildMiniMap();
    void UpdateTileColor(const std::size_t mapIndex);

    std::shared_ptr<MapData>                m_MapData;
    std::vector<std::shared_ptr<ColorCube>> m_ColorCubes;

    Util::ms_t m_LastPlayerChanged = 0;
    bool       m_PlayerStatus = false;
    double     m_Scale;

    Event::Remover m_UpdateHandle;
};
}  // namespace Dungeon

#endif  // MINIMAP_H
