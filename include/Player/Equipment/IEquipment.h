//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_IEquipment_H
#define FUCK_PTSD_IEquipment_H

#include "pch_extream.h"

#include "GameElement.h"
#include "TypeEquip.h"

class IEquipment {
public:
    enum Direction {
        ROW = 0,
        COL,
    };

    // setter
    [[noreturn]]
    virtual void setPosition(const glm::vec2 position) = 0;
    virtual void setWeaponType([[maybe_unused]] WeaponEnum::Type type) {
        return;
    };
    virtual void setShovelType([[maybe_unused]] ShovelEnum::Type type) {
        return;
    };

    [[maybe_unused]]
    virtual void PrepareThrowOut(bool state = false) {
        return;
    };

    // getter
    virtual Direction                    GetDirection() = 0;
    virtual bool                         GetIsThrow() { return false; };
    virtual std::shared_ptr<GameElement> GetGameObject() const = 0;

    //    virtual GameElement getWindowObject() = 0;
    //    virtual GameElement getItemObject() = 0;
};

#endif  // FUCK_PTSD_IEquipment_H
