//
// Created by adven on 2024/4/28.
//

#ifndef FUCK_PTSD_ITEMS_TOOLSYSTEM__1__HPP
#define FUCK_PTSD_ITEMS_TOOLSYSTEM__1__HPP

#include <map>
#include <memory>

// #include "Dungeon/Map.h"
#include "Game/Factory/ToolFactory.h"
#include "Game/Warehouse/Dagger.h"
#include "Game/Warehouse/IEquip.h"
#include "config.hpp"

namespace Players {
class Tools final {
public:
    Tools();

    void AddTool(const std::string& name, const std::string& type);

    void AddTool(
        const std::shared_ptr<IEquip>& ge,
        const std::string&             name,
        const std::string&             type
    );

    void RemoveTool(const std::string& name, const std::string& type);

    void DisappearTool(
        bool               visiable,
        const std::string& name,
        const std::string& type
    );

    template <typename T>
    std::shared_ptr<T> GetTool(
        std::size_t        idx,
        const std::string& expectedType
    ) {
        std::shared_ptr<T> result = nullptr;
        std::for_each(
            m_ToolList.begin(),
            m_ToolList.end(),
            [expectedType, &result](const auto& elem) {
                if (elem->GetType() == expectedType) {
                    result = elem;
                }
            }
        );

        if (!result) {
            throw std::runtime_error("not expected type");
        }
        return result;
    };

    std::vector<std::shared_ptr<IEquip>> GetAllTools();

    std::shared_ptr<Util::GameObject> GetGameObject();

private:
    void ReArrange();

    std::map<std::string, std::string> m_BaseTool = {
      {"BOMB", "1"},
      {"SHOVEL", "Shovel"},
      //      {"WEAPON", "Dagger"}};
      {"WEAPON", "Spear"}};
    std::shared_ptr<Util::GameElement> m_GameElement;

    std::vector<std::shared_ptr<IEquip>> m_ToolList;

    std::map<std::string, std::string>   m_BufferBase;
    std::vector<std::shared_ptr<IEquip>> m_BufferList;

    std::shared_ptr<Players::Items::ToolFactory> m_ToolFactory;

private:
    static constexpr glm::vec2 m_ColInitPos = {
      static_cast<int>(-WINDOW_WIDTH) / 2 + 65,
      static_cast<int>(WINDOW_HEIGHT) / 2 - 195};

    static constexpr glm::vec2 m_RowInitPos = {
      static_cast<int>(-WINDOW_WIDTH) / 2 + 65,
      static_cast<int>(WINDOW_HEIGHT) / 2 - 55};
};

}  // namespace Players

#endif  // FUCK_PTSD_ITEMS_TOOLSYSTEM__1__HPP
