#ifndef COLORCUBE_H
#define COLORCUBE_H

#include "Util/Image.hpp"

namespace Dungeon {
enum class CubeColor {
    black,
    blood,
    blue,
    confuse,
    crystal,
    darkpurple,
    dirt,
    gray,
    green,
    heal,
    metrognome,
    orange,
    purple,
    red,
    spore,
    water,
    white,
    yellow,
    yellowgreen
};

class ColorCube : public Core::Drawable {
public:
    ColorCube(Dungeon::CubeColor color);
    ~ColorCube() = default;
    void Draw(const Core::Matrices &data) override;
    glm::vec2 GetSize() const override;

private:
    void SetColor(Dungeon::CubeColor color);
    Dungeon::CubeColor m_Color;
    std::shared_ptr<Util::Image> m_Image;
};
} // namespace Dungeon

#endif // COLORCUBE_H
