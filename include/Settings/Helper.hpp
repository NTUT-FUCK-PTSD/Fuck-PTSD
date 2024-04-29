//
// Created by adven on 2024/4/26.
//

#ifndef FUCK_PTSD_HELPER_HPP
#define FUCK_PTSD_HELPER_HPP

#include <array>
#include <cstddef>
#include <exception>

#include <glm/vec2.hpp>

<<<<<<< HEAD
#include <exception>
=======
>>>>>>> main
#include "Dungeon/Map.h"

namespace Settings {
class Helper {
public:
<<<<<<< HEAD
    static void Init(Dungeon::Map* dungeonMap);

    static std::size_t GamePosToMapIdx(glm::ivec2 gamePos);
=======
    static void Init(Dungeon::Map* dungeonMap) { m_DungeonMap = dungeonMap; }

    static std::size_t GamePosToMapIdx(const glm::ivec2 gamePos) {
        return (gamePos.x - Dungeon::Map::GetLevelIndexMin().x + 1)
               + (gamePos.y - Dungeon::Map::GetLevelIndexMin().y + 1)
                     * Dungeon::Map::GetSize().x;
    };
>>>>>>> main

    struct PlayerPos {
        glm::vec2   GamePos;
        std::size_t MapIdx;
    };
    static PlayerPos GetPlayerPosDM();

<<<<<<< HEAD
    static glm::ivec2 Direct2MI(Player::Direction direction);

    static glm::vec2 CountImgPixel(
        const std::string& filePath,
        std::size_t        widthNumber,
        std::size_t        heightNumber
    );
=======
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
>>>>>>> main

private:
    static Dungeon::Map* m_DungeonMap;
};
}  // namespace Settings

#endif  // FUCK_PTSD_HELPER_HPP
