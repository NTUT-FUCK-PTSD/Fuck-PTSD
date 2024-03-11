//
// Created by adven on 2024/3/2.
//

#ifndef FUCK_PTSD_TOOLBOXS_H
#define FUCK_PTSD_TOOLBOXS_H

#include "Util/Image.hpp"

class ToolBoxs {
public:
    static bool IsAnyKeyPress();
    static glm::vec2 CountImagePixel(const std::string &ImagePath,
                                     uint16_t WidthNumber,
                                     uint16_t HeightNumber);
    static glm::vec2 AddVec2(const glm::vec2 &add01, const glm::vec2 &add02);

    static int FrameCounter(const int current_frame);
};

#endif // FUCK_PTSD_TOOLBOXS_H
