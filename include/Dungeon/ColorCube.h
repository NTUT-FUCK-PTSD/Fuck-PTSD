#ifndef COLORCUBE_H
#define COLORCUBE_H

#include "Util/Image.hpp"

#include <map>

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
    stone,
    wall,
    water,
    white,
    yellow,
    yellowgreen
};

class ColorCube final : public Core::Drawable {
public:
    ColorCube(Dungeon::CubeColor color);
    ColorCube();
    ~ColorCube() = default;
    void Draw(const Core::Matrices &data) override;
    glm::vec2 GetSize() const override;
    bool GetAvailable() const;
    void SetColor(Dungeon::CubeColor color);
    Dungeon::CubeColor GetColor() const;
    static void InitColorMap();

private:
    Dungeon::CubeColor m_Color;

    static std::map<Dungeon::CubeColor, std::unique_ptr<Util::Image>>
        m_ColorMap;
    static bool m_ColorMapInitialized;

    bool m_Available = false;
};
} // namespace Dungeon

#endif // COLORCUBE_H
