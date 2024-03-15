//
// Created by adven on 2024/3/2.
//

#ifndef FUCK_PTSD_TOOLBOXS_H
#define FUCK_PTSD_TOOLBOXS_H

#include "Util/Image.hpp"

class ToolBoxs {
public:
    static bool IsAnyKeyPress();
    static glm::vec2 CountImagePixel(std::string &ImagePath,
                                     uint16_t WidthNumber,
                                     uint16_t HeightNumber);
};

#endif // FUCK_PTSD_TOOLBOXS_H
