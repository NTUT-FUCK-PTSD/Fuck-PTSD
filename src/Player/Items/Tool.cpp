//
// Created by 陳世昂 on 2024/4/29.
//

#include <exception>
#include "Produce/Dagger.h"

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

    ReArrange();
};

std::shared_ptr<IEquip> Players::Tools::GetTool(std::size_t idx) {
    if (idx >= m_ToolList.size()) {
        throw std::runtime_error("tools idx is out of range");
    }

    return m_ToolList.at(idx);
}

template <class T>
T* Players::Tools::GetTool(std::size_t idx) {
    return dynamic_cast<T>(m_ToolList.at(2).get());
}

std::vector<std::shared_ptr<IEquip>> Players::Tools::GetAllTools() {
    return m_ToolList;
}

std::shared_ptr<Util::GameObject> Players::Tools::GetGameObject()  {
    return static_cast<std::shared_ptr<Util::GameObject>>(m_GameElement);
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
        initCol += glm::vec2{0, 140};
    }
}
