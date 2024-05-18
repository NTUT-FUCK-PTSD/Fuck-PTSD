#ifndef FUCK_PTSD_WINDOW_HPP
#define FUCK_PTSD_WINDOW_HPP

#include "pch.hpp"  // IWYU pragma: export

class Window {
public:
    static void             Init();
    static constexpr double TileWidth = 24.0;
    static constexpr double ColNumber = 20.0;
    static double           RowNumber;
    static double           Scale;

    static double HalfColNumber;
    static double HalfRowNumber;

    static glm::vec2 GetScale() { return {Scale, Scale}; };
};

#endif  // FUCK_PTSD_WINDOW_HPP
