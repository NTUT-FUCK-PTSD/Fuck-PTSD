#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "Util/Text.hpp"

#include "Dungeon/Map.h"

namespace Dungeon {

class MapHandler final : public Core::Drawable {
public:
    MapHandler(const std::shared_ptr<Map> map);
    void      Draw(const Core::Matrices& data) override;
    glm::vec2 GetSize() const override;
    void      ChangeEasterEggColor();
    void      EasterEgg();

private:
    std::shared_ptr<Util::Image> m_Image;
    std::shared_ptr<Util::Image> m_EasterEgg;
    const std::shared_ptr<Map>   m_Map;
    Util::Transform              m_Transform;
};

}  // namespace Dungeon

#endif  // MAP_HANDLER_H
