//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_WEAPON_H
#define FUCK_PTSD_WEAPON_H

#include "IEquipment.h"
#include "ToolBoxs.h"
#include "Weapon/IBaseWeapon.h"
#include "Weapon/Dagger.hpp"
#include "pch_extream.h"

class Weapon final : public IEquipment {
public:
    enum Type { DAGGER = 0, BROADSWORD, RAPIER };

    explicit Weapon();
//    virtual ~Weapon() = 0;

    void setType(Weapon::Type type);
    void setPosition(const glm::vec2 position) override;

    [[nodiscard]] std::shared_ptr<GameElement> GetGameObject() const override;

private:
    void rendererWindow();
    void rendererItem();

    std::size_t m_ZIndex = 50;
    glm::vec2 m_Scale = {3, 3};
    glm::vec2 m_Position = {0, 0};

    //    ASSETS_DIR "/gui/diamond.png"

    std::string m_ImagePathWindow = ASSETS_DIR "/gui/hud_slot_2.png";
    std::shared_ptr<IBaseWeapon> m_ItemType;
    //    std::string m_ImagePathItem = ASSETS_DIR "/items/weapon_dagger.png";
    std::string m_ImagePathItem;

    std::shared_ptr<GameElement> m_Window = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Item = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Attack = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_WEAPON_H
