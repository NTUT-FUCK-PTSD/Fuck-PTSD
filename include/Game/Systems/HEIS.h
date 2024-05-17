//
// Created by adven on 2024/5/1.
//

#ifndef FUCK_PTSD_HEIS_H
#define FUCK_PTSD_HEIS_H
/**
 * @note handle-enemy-interactive-system
 */
#include "Dungeon/Map.h"
#include "Player.h"

namespace Game::Systems {
class HEIS final {
public:
    static auto Init(Dungeon::Map* dungeon) -> void;

private:
    static Dungeon::Map* m_Map;

public:
    static auto MakeTile(
        glm::ivec2  direGP,
        glm::ivec2  playerGP,
        std::string weaponType
    ) -> void;
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HEIS_H
