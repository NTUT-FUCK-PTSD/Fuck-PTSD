#include "Game/Factory/ToolFactory.h"

#include "Game/Warehouse/Bomb.h"
#include "Game/Warehouse/Dagger.h"
#include "Game/Warehouse/Shovel.h"

std::shared_ptr<IEquip> Players::Items::ToolFactory::MakeTool(
    const std::string& name,
    const std::string& type
) {
    switch (Settings::Hash::HashConvert(name)) {
    case "BOMB"_hash: GenBomb(type); break;
    case "SHOVEL"_hash: GenShovel(type); break;
    case "WEAPON"_hash: GenWeapon(type); break;
    default: throw std::runtime_error("Tools type is not available"); break;
    }

    return m_Result;
}

void Players::Items::ToolFactory::GenBomb(const std::string& type) {
    m_Result = std::make_shared<Bomb>(std::stoi(type));
}

void Players::Items::ToolFactory::GenShovel(const std::string& type) {
    switch (Settings::Hash::HashConvert(type)) {
    case "Shovel"_hash: m_Result = std::make_shared<Shovel>(); break;
    default: throw std::runtime_error("Shovel's type is not available");
    }
}

void Players::Items::ToolFactory::GenWeapon(const std::string& type) {
    switch (Settings::Hash::HashConvert(type)) {
    case "Dagger"_hash: m_Result = std::make_shared<Dagger>(); break;
    default: throw std::runtime_error("Shovel's type is not available");
    }
}
