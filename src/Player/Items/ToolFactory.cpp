#include "Player/Factory/ToolFactory.h"

#include "Produce/Bomb.h"
#include "Produce/Dagger.h"
#include "Produce/Shovel.h"

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
