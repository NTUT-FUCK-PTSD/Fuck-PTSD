#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "Util/Text.hpp"

#include "Dungeon/Map.h"

namespace Dungeon {

class MapHandler final : public Core::Drawable {
public:
    MapHandler(const std::shared_ptr<Map> map);
    void Draw(const Core::Matrices &data) override;
    glm::vec2 GetSize() const override { return m_Image->GetSize(); }

private:
    std::shared_ptr<Util::Image> m_Image;
    const std::shared_ptr<Map> m_Map;
};

} // namespace Dungeon

#endif // MAP_HANDLER_H
