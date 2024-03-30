//
// Created by adven on 2024/3/2.
//

#ifndef FUCK_PTSD_TOOLBOXS_H
#define FUCK_PTSD_TOOLBOXS_H

#include "Util/Image.hpp"

class ToolBoxs final {
public:
    static bool IsAnyKeyPress();
    static glm::vec2 CountImagePixel(const std::string &ImagePath,
                                     uint16_t WidthNumber,
                                     uint16_t HeightNumber);
    static glm::vec2 AddVec2(const glm::vec2 &add01, const glm::vec2 &add02);

    static glm::vec2 GamePostoPos(const glm::vec2 &gamePosition);
    static glm::vec2 PosToGamePos(const glm::vec2 &position);
};

#endif // FUCK_PTSD_TOOLBOXS_H
