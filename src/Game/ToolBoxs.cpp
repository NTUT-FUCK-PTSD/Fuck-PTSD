//
// Created by adven on 2024/3/2.
//

#include "ToolBoxs.h"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "Settings/Window.hpp"

bool ToolBoxs::IsAnyKeyPress() {
    for (int i = 0; i < 512; i++) {
        if (Util::Input::IsKeyPressed((Util::Keycode)i)) {
            return true;
        }
    }
    return false;
}

glm::vec2 ToolBoxs::CountImagePixel(
    const std::string& ImagePath,
    const uint16_t     WidthNumber,
    const uint16_t     HeightNumber
) {
    const auto ImageSize = Util::Image(ImagePath).GetSize();

    const auto result = glm::vec2(
        ImageSize[0] / (double)WidthNumber,
        ImageSize[1] / (double)HeightNumber
    );

    return result;
}

glm::vec2 ToolBoxs::AddVec2(const glm::vec2& add01, const glm::vec2& add02) {
    glm::vec2 result = {add01[0] + add02[0], add01[1] + add02[1]};
    return result;
}

glm::vec2 ToolBoxs::GamePostoPos(const glm::vec2& gamePosition) {
    return {
      gamePosition.x * DUNGEON_TILE_WIDTH * DUNGEON_SCALE,
      -gamePosition.y * DUNGEON_TILE_WIDTH * DUNGEON_SCALE
    };
}

glm::vec2 ToolBoxs::PosToGamePos(const glm::vec2& position) {
    return {
      position.x / DUNGEON_TILE_WIDTH / DUNGEON_SCALE,
      -position.y / DUNGEON_TILE_WIDTH / DUNGEON_SCALE
    };
}
