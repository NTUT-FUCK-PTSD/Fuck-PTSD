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
    static void Init(Dungeon::Map* dungeonMap);

    static std::size_t GamePosToMapIdx(glm::ivec2 gamePos);

    struct PlayerPos {
        glm::vec2   GamePos;
        std::size_t MapIdx;
    };
    static PlayerPos GetPlayerPosDM();

    static glm::ivec2 Direct2MI(Player::Direction direction);

    static glm::vec2 CountImgPixel(
        const std::string& filePath,
        std::size_t        widthNumber,
        std::size_t        heightNumber
    );

private:
    static Dungeon::Map* m_DungeonMap;
};
}  // namespace Settings

#endif  // FUCK_PTSD_HELPER_HPP
