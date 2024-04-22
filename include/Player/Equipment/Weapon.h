//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_WEAPON_H
#define FUCK_PTSD_WEAPON_H

#include "IEquipment.h"
#include "ToolBoxs.h"
#include "TypeEquip.h"
#include "Weapon/Component.h"
#include "Weapon/EntityBroadsword.h"
#include "Weapon/EntityDagger.h"
#include "Weapon/EntityRapier.h"
#include "pch_extream.h"

class Weapon final : public IEquipment {
public:
    explicit Weapon(WeaponEnum::Type type);
    virtual ~Weapon() = default;

    void setWeaponType(WeaponEnum::Type type) override;
    void setPosition(const glm::vec2 position) override;

    [[nodiscard]]
    std::shared_ptr<GameElement> GetGameObject() const override;
    [[nodiscard]]
    bool GetIsThrow() override;

    Direction GetDirection() override { return IEquipment::Direction::ROW; };

private:
    void selectWeaponType(WeaponEnum::Type type);
    void rendererWindow();
    void rendererItem();

    std::size_t m_ZIndex = 99;
    glm::vec2   m_Scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    glm::vec2   m_Position = {0, 0};

    std::string                              m_ImagePathItem;
    std::shared_ptr<ToolSystem::TBaseWeapon> m_ItemType;
    std::string m_ImagePathWindow = ASSETS_DIR "/gui/hud_slot_2.png";

    std::shared_ptr<GameElement> m_Window = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Item = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Attack = std::make_shared<GameElement>();
};

#endif  // FUCK_PTSD_WEAPON_H
