//
// Created by adven on 2024/4/26.
//

#ifndef FUCK_PTSD_HELPER_HPP
#define FUCK_PTSD_HELPER_HPP

#include <array>
#include <cstddef>

#include <glm/vec2.hpp>

#include "Dungeon/Map.h"

namespace Settings {
class Helper {
public:
    static std::size_t GamePosToMapIdx(const glm::ivec2 gamePos) {
      return (gamePos.x - Dungeon::Map::m_Level->GetLevelIndexMin().x + 1)
             + (gamePos.y - Dungeon::Map::m_Level->GetLevelIndexMin().y + 1) * Dungeon::Map::m_Size.x;
    };
};
}

#endif  // FUCK_PTSD_HELPER_HPP
