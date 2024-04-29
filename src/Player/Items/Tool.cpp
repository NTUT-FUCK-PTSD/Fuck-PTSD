//
// Created by 陳世昂 on 2024/4/29.
//

#include "Player/Items/Tools.h"

Players::Tools::Tools() {
    m_ToolFactory = std::make_shared<Players::Items::ToolFactory>();

    m_GameElement = std::make_shared<Util::GameElement>();
    m_GameElement->SetVisible(false);

    for (const auto& elem : m_BaseTool) {
        const auto& obj = m_ToolFactory->MakeTool(elem.first, elem.second);

        m_ToolList.push_back(obj);
        m_GameElement->AddChild(obj);
    }

    ReArrange();
};

void Players::Tools::AddTool(const std::shared_ptr<IEquip>& ge) {
    m_ToolList.push_back(ge);
    m_GameElement->AddChild(ge);
};

std::shared_ptr<Util::GameObject> Players::Tools::GetGameObject()  {
    return static_cast<std::shared_ptr<Util::GameObject>>(m_GameElement);
}

void Players::Tools::RePosition() {
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

void Players::Tools::ReArrange() {

    auto initCol = m_ColInitPos;
    auto initRow = m_RowInitPos;

    for (const auto& elem : m_ToolList) {
        if (elem->GetWinPos() == IEquip::ROW) {
            elem->SetPosition(initRow);
            initRow += glm::vec2{-100, 0};
            continue;
        }
        elem->SetPosition(initCol);
        LOG_INFO(initCol);
//        elem->SetPosition({-655,-335});
        initCol += glm::vec2{0, 140};
    }
}
