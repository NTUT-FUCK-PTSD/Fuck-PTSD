//
// Created by adven on 2024/4/28.
//

#ifndef FUCK_PTSD_TOOLSYSTEM_HPP
#define FUCK_PTSD_TOOLSYSTEM_HPP

#include <map>
#include "Player/Equipment/IEquip.h"
#include "ToolFactory.h"
class Tool final {
public:
    explicit Tool() {
        m_ToolFactory = std::make_shared<Players::Items::ToolFactory>();
        m_GameElement = std::make_shared<GameElement>();
        m_GameElement->SetVisible(false);

        for (const auto& elem : m_BaseTool) {
            const auto& obj = m_ToolFactory->MakeTool(elem.first, elem.second);

            m_ToolList.push_back(obj);
            m_GameElement->AddChild(obj);
        }
    };

    void AddTool(const std::shared_ptr<IEquip>& ge) {
        m_ToolList.push_back(ge);
        m_GameElement->AddChild(ge);
    };

    std::shared_ptr<Util::GameObject> GetGameObject() {
        return static_cast<std::shared_ptr<Util::GameObject>>(m_GameElement);
    }

private:
    const std::map<std::string, std::string> m_BaseTool = {
      {"BOMB", "1"},
      {"SHOVEL", "Shovel"},
      {"WEAPON", "Dagger"}};

    std::vector<std::shared_ptr<IEquip>> m_ToolList;

    std::shared_ptr<Players::Items::ToolFactory> m_ToolFactory;

    std::shared_ptr<GameElement> m_GameElement;
};

#endif  // FUCK_PTSD_TOOLSYSTEM_HPP
