#ifndef MINIMAP_H
#define MINIMAP_H

#include "Util/GameObject.hpp"
#include "Util/Time.hpp"

#include "Dungeon/ColorCube.h"
#include "Dungeon/MapData.h"

namespace Dungeon {
class MiniMap : public Util::GameObject {
public:
    MiniMap(std::shared_ptr<MapData> mapData);
    ~MiniMap() = default;
    glm::vec2 GetSize() const;
    void SetColor(const glm::vec2 &position, CubeColor color);
    void SetVisible(const glm::vec2 &position, bool visible);
    void SetVisible(const std::size_t position, bool visible);
    void SetScale(double scale);

    void Update();

private:
    void BuildMiniMap();
    void UpdateTileColor(const std::size_t mapIndex);
    void AddChildren(const std::vector<std::shared_ptr<GameObject>> &children);
    void
    RemoveChildren(const std::vector<std::shared_ptr<GameObject>> &children);

    std::shared_ptr<MapData> m_MapData;
    std::vector<std::shared_ptr<ColorCube>> m_ColorCubes;

    Util::ms_t m_LastPlayerChanged = 0;
    bool m_PlayerStatus = false;
    double m_Scale = DUNGEON_SCALE + 1;
};
} // namespace Dungeon

#endif // MINIMAP_H
