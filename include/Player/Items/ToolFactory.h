//
// Created by adven on 2024/4/28.
//

#ifndef FUCK_PTSD_TOOLFACTORY_H
#define FUCK_PTSD_TOOLFACTORY_H

#include "Player/Equipment/IEquip.h"
#include "Settings/Hash.h"

using namespace Settings::Hash;

namespace Players::Items {
class ToolFactory {
public:
    explicit ToolFactory() = default;

    std::shared_ptr<IEquip> MakeTool(
        const std::string& name,
        const std::string& type
    ) {
        switch (Settings::Hash::HashConvert(name)) {
        case "BOMB"_hash: GenBomb(); break;
        case "SHOVEL"_hash: GenShovel(); break;
        case "WEAPON"_hash: GenWeapon(); break;
        default: throw std::runtime_error("Tool type is not available"); break;
        }

        return m_Result;
    };

private:
    void GenBomb();
    void GenShovel();
    void GenWeapon();

    std::shared_ptr<IEquip> m_Result;
};
}  // namespace Players::Items

#endif  // FUCK_PTSD_TOOLFACTORY_H
