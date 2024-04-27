#ifndef FUCK_PTSD_GAME_SYSTEM_MAIN_H
#define FUCK_PTSD_GAME_SYSTEM_MAIN_H

#include <vector>
#include "Util/GameObject.hpp"

#include "Dungeon/Map.h"
#include "Graphs/Base.h"

namespace Game {
class System final {
public:
    static void Init(Dungeon::Map *dungeonMap);

    static void AddWeapon(std::shared_ptr<Game::Graphs::IBase> baseType, const std::size_t posMI);

    static std::shared_ptr<Util::GameObject> GetGameObject();

    static void Update();

private:
    static Dungeon::Map *m_DungeonMap;

    static std::vector<std::shared_ptr<Game::Graphs::IBase>> m_IBaseList;
};

}  // namespace Game

#endif  // FUCK_PTSD_GAME_SYSTEM_MAIN_H
