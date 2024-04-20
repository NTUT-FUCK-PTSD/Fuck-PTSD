//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_SHOVEL_H
#define FUCK_PTSD_SHOVEL_H

#include "IEquipment.h"
#include "Shovel/EntityShovel.h"
#include "Shovel/SComponent.h"
#include "ToolBoxs.h"
#include "pch_extream.h"

class Shovel final : public IEquipment {
public:
    explicit Shovel(ShovelEnum::Type type);

    void setPosition(const glm::vec2 position) override;
    void setShovelType(ShovelEnum::Type type) override;

    std::shared_ptr<GameElement> GetGameObject() const override;
    Direction GetDirection() override { return IEquipment::Direction::ROW; };

private:
    void selectWeaponType(ShovelEnum::Type type);
    void rendererWindow();
    void rendererItem();

    std::size_t m_ZIndex = 99;
    glm::vec2 m_Scale = {3, 3};
    glm::vec2 m_Position = {0, 0};

    std::shared_ptr<ToolSystem::TBaseShovel> m_ItemType;
    std::string m_ImagePathWindow = ASSETS_DIR "/gui/hud_slot_1.png";
    std::string m_ImagePathItem;

    std::shared_ptr<GameElement> m_Window = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Item = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Shovel = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_SHOVEL_H
