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
    static void Init(Dungeon::Map* dungeonMap) {
        m_DungeonMap = dungeonMap;
    }

    static std::size_t GamePosToMapIdx(const glm::ivec2 gamePos) {
      return (gamePos.x - Dungeon::Map::m_Level->GetLevelIndexMin().x + 1)
             + (gamePos.y - Dungeon::Map::m_Level->GetLevelIndexMin().y + 1) * Dungeon::Map::m_Size.x;
    };

    struct PlayerPos {
      glm::vec2 GamePos;
      std::size_t MapIdx;
    };
    static PlayerPos GetPlayerPosDM() {
        const auto playerPos = m_DungeonMap->GetMapData()->GetPlayerPosition();
        const auto typeChange = static_cast<glm::ivec2>(playerPos);
        const auto mapIdx = GamePosToMapIdx(typeChange);

        return PlayerPos {
          playerPos, mapIdx
        };
    };
private:
    static Dungeon::Map* m_DungeonMap;
};
}

#endif  // FUCK_PTSD_HELPER_HPP
