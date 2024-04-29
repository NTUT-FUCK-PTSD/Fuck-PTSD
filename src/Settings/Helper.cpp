//
// Created by 陳世昂 on 2024/4/26.
//

#include "Helper.hpp"

void Settings::Helper::Init(Dungeon::Map* dungeonMap) {
    m_DungeonMap = dungeonMap;
}

std::size_t Settings::Helper::GamePosToMapIdx(glm::ivec2 gamePos) {
    return (gamePos.x - Dungeon::Map::m_Level->GetLevelIndexMin().x + 1)
           + (gamePos.y - Dungeon::Map::m_Level->GetLevelIndexMin().y + 1)
                 * Dungeon::Map::m_Size.x;
};

Settings::Helper::PlayerPos Settings::Helper::GetPlayerPosDM() {
    {
        const auto playerPos = m_DungeonMap->GetMapData()->GetPlayerPosition();
        const auto typeChange = static_cast<glm::ivec2>(playerPos);
        const auto mapIdx = GamePosToMapIdx(typeChange);

        return PlayerPos{playerPos, mapIdx};
    };
}

glm::ivec2 Settings::Helper::Direct2MI(Player::Direction direction) {
    switch (direction) {
    case Player::Direction::UP: return {0, -1};
    case Player::Direction::LEFT: return {-1, 0};
    case Player::Direction::DOWN: return {0, 1};
    case Player::Direction::RIGHT: return {1, 0};
    case Player::Direction::NONE:
        throw std::runtime_error("direction can not be none");
    }
}

glm::vec2 Settings::Helper::CountImgPixel(
    const std::string& filePath,
    std::size_t        widthNumber,
    std::size_t        heightNumber
) {
    const auto ImageSize = Util::Image(filePath).GetSize();

    const auto result = glm::vec2(
        ImageSize[0] / static_cast<float>(widthNumber),
        ImageSize[1] / static_cast<float>(widthNumber)
    );

    return result;
}
Dungeon::Map* Settings::Helper::m_DungeonMap = nullptr;
