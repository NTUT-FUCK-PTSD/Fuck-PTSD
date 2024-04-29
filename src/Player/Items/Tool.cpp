//
// Created by 陳世昂 on 2024/4/29.
//

#include "Player/Items/Tool.h"

#include "Dungeon/Map.h"

Tool::Tool() {
    m_ToolFactory = std::make_shared<Players::Items::ToolFactory>();

    m_GameElement = std::make_shared<GameElement>();
    m_GameElement->SetVisible(false);

    for (const auto& elem : m_BaseTool) {
        const auto& obj = m_ToolFactory->MakeTool(elem.first, elem.second);

        m_ToolList.push_back(obj);
        m_GameElement->AddChild(obj);
    }

    RePosition();
};

void Tool::AddTool(const std::shared_ptr<IEquip>& ge) {
    m_ToolList.push_back(ge);
    m_GameElement->AddChild(ge);
};

std::shared_ptr<Util::GameObject> Tool::GetGameObject()  {
    return static_cast<std::shared_ptr<Util::GameObject>>(m_GameElement);
}

void Tool::RePosition() {
    std::vector<glm::vec2> pos = {
      {-int(WINDOW_WIDTH) / 2 + 65, WINDOW_HEIGHT / 2 - 55},
      {-int(WINDOW_WIDTH) / 2 + 65, WINDOW_HEIGHT / 2 - 195},
      {-int(WINDOW_WIDTH) / 2 + 65, WINDOW_HEIGHT / 2 - 335},
    };

    std::size_t idx = 0;
    for (const auto& elem : m_ToolList) {
        elem->SetPosition(pos[idx++]);
    }
}
