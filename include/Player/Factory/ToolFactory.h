//
// Created by adven on 2024/4/28.
//

#ifndef FUCK_PTSD_TOOLFACTORY_H
#define FUCK_PTSD_TOOLFACTORY_H

#include <any>
#include <memory>
#include "Player/Factory/IEquip.h"
#include "Settings/Hash.h"

using namespace Settings::Hash;

namespace Players::Items {
class ToolFactory {
public:
    explicit ToolFactory() = default;

    [[nodiscard]]
    std::shared_ptr<IEquip> MakeTool(
        const std::string& name,
        const std::string& type
    );

private:
    void                    GenBomb(const std::string& type);
    void                    GenShovel(const std::string& type);
    void                    GenWeapon(const std::string& type);
    std::shared_ptr<IEquip> m_Result;
};
}  // namespace Players::Items

#endif  // FUCK_PTSD_TOOLFACTORY_H
