#ifndef MINIMAP_H
#define MINIMAP_H

#include "Util/GameObject.hpp"

#include "Dungeon/ColorCube.h"
#include "Dungeon/MapData.h"

namespace Dungeon {
class MiniMap : public Util::GameObject {
public:
    MiniMap(std::shared_ptr<MapData> mapData);
    ~MiniMap() = default;
    glm::vec2 GetSize() const;
    void SetColor(const glm::vec2 &position, CubeColor color);

private:
    std::shared_ptr<MapData> m_MapData;
    std::vector<std::shared_ptr<ColorCube>> m_ColorCubes;
};
} // namespace Dungeon

#endif // MINIMAP_H
