//
// Created by adven on 2024/4/26.
//

#ifndef FUCK_PTSD_HELPER_HPP
#define FUCK_PTSD_HELPER_HPP

#include <array>
#include <cstddef>
#include <exception>

#include <glm/vec2.hpp>

#include "Dungeon/Map.h"

namespace Settings {
class Helper {
public:
    static void Init(Dungeon::Map* dungeonMap) { m_DungeonMap = dungeonMap; }

    static std::size_t GamePosToMapIdx(const glm::ivec2 gamePos) {
        return (gamePos.x - Dungeon::Map::GetLevelIndexMin().x + 1)
               + (gamePos.y - Dungeon::Map::GetLevelIndexMin().y + 1)
                     * Dungeon::Map::GetSize().x;
    };

    struct PlayerPos {
        glm::vec2   GamePos;
        std::size_t MapIdx;
    };
    static PlayerPos GetPlayerPosDM() {
        const auto playerPos = m_DungeonMap->GetMapData()->GetPlayerPosition();
        const auto typeChange = static_cast<glm::ivec2>(playerPos);
        const auto mapIdx = GamePosToMapIdx(typeChange);

        return PlayerPos{playerPos, mapIdx};
    };

    inline static glm::ivec2 Direct2MI(Player::Direction direction) {
        switch (direction) {
        case Player::Direction::UP: return {0, -1};
        case Player::Direction::LEFT: return {-1, 0};
        case Player::Direction::DOWN: return {0, 1};
        case Player::Direction::RIGHT: return {1, 0};
        case Player::Direction::NONE:
            throw std::runtime_error("direction can not be none");
        }
    }

private:
    static Dungeon::Map* m_DungeonMap;
};
}  // namespace Settings

#endif  // FUCK_PTSD_HELPER_HPP
