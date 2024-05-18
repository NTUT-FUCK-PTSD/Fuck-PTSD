//
// Created by 陳世昂 on 2024/4/29.
//

#include <exception>
#include <iterator>
#include "Game/Warehouse/Dagger.h"

#include "Game/Warehouse/Tools.h"

Players::Tools::Tools() {
    m_ColInitPos = {
      static_cast<int>(-PTSD_Config::WINDOW_WIDTH) / 2 + 65,
      static_cast<int>(PTSD_Config::WINDOW_HEIGHT) / 2 - 195
    };
    m_RowInitPos = {
      static_cast<int>(-PTSD_Config::WINDOW_WIDTH) / 2 + 65,
      static_cast<int>(PTSD_Config::WINDOW_HEIGHT) / 2 - 55
    };
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

std::shared_ptr<IEquip> Players::Tools::GetWeapon() {
    const auto& iter = std::find_if(
        m_ToolList.begin(),
        m_ToolList.end(),
        [](const auto& elem) { return elem->GetName() == "WEAPON"; }
    );

    return *iter;
}

void Players::Tools::DisappearTool(
    bool               visiable,
    const std::string& name,
    const std::string& type
) {
    if (!visiable) {
        const auto& it = m_BaseTool.find(name);
        m_BufferBase.insert({it->first, it->second});

        std::for_each(
            m_ToolList.begin(),
            m_ToolList.end(),
            [&](const auto& elem) {
                if (elem->GetName() == name && elem->GetType() == type
                    || (elem->GetName() == "THROW" && elem->GetType() == type))
                    m_BufferList.push_back(elem);
            }
        );
        RemoveTool(name, type);
    } else {
        const auto& it = m_BufferBase.find(name);
        if (it == m_BufferBase.end()) {
            LOG_ERROR("ReAdd Tool Error");
            return;
            // throw std::runtime_error("Remove Tool Error");
        }
        m_BufferBase.erase(it);

        for (auto i = 0; i < m_BufferList.size(); i++) {
            AddTool(
                m_BufferList[i],
                m_BufferList[i]->GetName(),
                m_BufferList[i]->GetType()
            );
        }
        m_BufferList.clear();
    }
}

void Players::Tools::RemoveTool(
    const std::string& name,
    const std::string& type
) {
    const auto& it = m_BaseTool.find(name);
    if (m_BaseTool.end() == it) {
        LOG_ERROR("ReAdd Tool Error");
        return;
        // throw std::runtime_error("Remove Tool Error");
    }
    m_BaseTool.erase(it);

    auto removeElem = [&](std::size_t i, std::size_t offset) {
        const auto& elem = m_ToolList[i];
        m_ToolList.erase(m_ToolList.begin() + i - offset);

        m_GameElement->RemoveChild(elem);
    };

    std::vector<std::size_t> removeList = {};

    for (std::size_t i = 0; i < m_ToolList.size(); i++) {
        auto test = m_ToolList[i]->GetName();
        auto test0 = m_ToolList[i]->GetType();
        if (m_ToolList[i]->GetName() == name
            && m_ToolList[i]->GetType() == type) {
            removeList.push_back(i);
        } else if (m_ToolList[i]->GetName() == "THROW"
                   && m_ToolList[i]->GetType() == type) {
            removeList.push_back(i);
        }
    }

    std::size_t count = 0;
    std::for_each(
        removeList.begin(),
        removeList.end(),
        [removeElem, &count, this](auto idx) {
            const auto& elem = m_ToolList[idx - count];
            m_GameElement->RemoveChild(elem);
            m_ToolList.erase(m_ToolList.begin() + idx - count);
            count++;
        }
    );

    ReArrange();
}

void Players::Tools::AddTool(const std::string& name, const std::string& type) {
    const auto& obj = m_ToolFactory->MakeTool(name, type);
    m_BaseTool.insert({name, type});
    m_ToolList.insert(m_ToolList.end(), obj);
    m_GameElement->AddChild(obj);

    ReArrange();
}

void Players::Tools::AddTool(
    const std::shared_ptr<IEquip>& ge,
    const std::string&             name,
    const std::string&             type
) {
    if (ge->GetName() != name || ge->GetType() != type) {
        throw std::runtime_error("type or name not match");
    }

    m_BaseTool.insert({name, type});
    if (ge->GetWinPos() == IEquip::ROW) {
        m_ToolList.insert(m_ToolList.end(), ge);
    } else {
        m_ToolList.insert(m_ToolList.begin(), ge);
    }
    m_GameElement->AddChild(ge);

    ReArrange();
}

std::vector<std::shared_ptr<IEquip>> Players::Tools::GetAllTools() {
    return m_ToolList;
}

std::shared_ptr<Util::GameObject> Players::Tools::GetGameObject() {
    return static_cast<std::shared_ptr<Util::GameObject>>(m_GameElement);
}

void Players::Tools::ReArrange() {
    auto initCol = m_ColInitPos;
    auto initRow = m_RowInitPos;

    for (const auto& elem : m_ToolList) {
        if (elem->GetWinPos() == IEquip::ROW) {
            elem->SetPosition(initRow);
            initRow += glm::vec2{100, 0};
            continue;
        }
        elem->SetPosition(initCol);
        //        initCol += glm::vec2{0, 140};
        initCol += glm::vec2{0, -140};
    }
}
