//
// Created by adven on 2024/4/28.
//

#ifndef FUCK_PTSD_ITEMS_TOOLSYSTEM__1__HPP
#define FUCK_PTSD_ITEMS_TOOLSYSTEM__1__HPP

#include <map>

//#include "Dungeon/Map.h"
#include "config.hpp"
#include "Player/Factory/IEquip.h"
#include "Player/Factory/ToolFactory.h"

namespace Players {
class Tools final {
public:
    explicit Tools();

    void AddTool(const std::shared_ptr<IEquip>& ge);

    std::shared_ptr<Util::GameObject> GetGameObject();

private:
    void RePosition();
    void ReArrange();

    const std::map<std::string, std::string> m_BaseTool = {
      {"BOMB", "1"},
      {"SHOVEL", "Shovel"},
      {"WEAPON", "Dagger"}};

    std::shared_ptr<Util::GameElement> m_GameElement;

    std::vector<std::shared_ptr<IEquip>> m_ToolList;

    std::shared_ptr<Players::Items::ToolFactory> m_ToolFactory;

private:
    static constexpr glm::vec2 m_ColInitPos = {
      static_cast<int>(-WINDOW_WIDTH) / 2 + 65,
      static_cast<int>(WINDOW_HEIGHT) / 2 - 195};

    static constexpr glm::vec2 m_RowInitPos = {
      static_cast<int>(-WINDOW_WIDTH) / 2 + 165,
      static_cast<int>(WINDOW_HEIGHT) / 2 - 55};
};
}

#endif  // FUCK_PTSD_ITEMS_TOOLSYSTEM__1__HPP
