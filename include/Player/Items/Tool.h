//
// Created by adven on 2024/4/28.
//

#ifndef FUCK_PTSD_ITEMS_TOOLSYSTEM_HPP
#define FUCK_PTSD_ITEMS_TOOLSYSTEM_HPP

#include <map>
#include "Player/Factory/IEquip.h"
#include "Player/Factory/ToolFactory.h"

class Tool final {
public:
    explicit Tool();

    void AddTool(const std::shared_ptr<IEquip>& ge);

    std::shared_ptr<Util::GameObject> GetGameObject();

private:
    void RePosition();

    const std::map<std::string, std::string> m_BaseTool =
        {{"BOMB", "1"}, {"SHOVEL", "Shovel"}, {"WEAPON", "Dagger"}};

    std::shared_ptr<GameElement> m_GameElement;

    std::vector<std::shared_ptr<IEquip>> m_ToolList;

    std::shared_ptr<Players::Items::ToolFactory> m_ToolFactory;
};

#endif  // FUCK_PTSD_ITEMS_TOOLSYSTEM_HPP
