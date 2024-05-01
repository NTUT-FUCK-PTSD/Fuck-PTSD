//
// Created by adven on 2024/5/1.
//

#ifndef FUCK_PTSD_HEIS_H
#define FUCK_PTSD_HEIS_H
/**
 * @note handle-enemy-interactive-system
 */
#include "Dungeon/Map.h"

namespace Game::Systems {
class HEIS {
public:
    static auto Init(Dungeon::Map* dungeon) -> void;

    static auto DetectHealth(std::size_t mi) -> void;

private:
    static Dungeon::Map* m_Map;
};
}  // namespace Game::Systems

#endif  // FUCK_PTSD_HEIS_H
