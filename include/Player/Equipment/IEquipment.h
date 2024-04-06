//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_IEquipment_H
#define FUCK_PTSD_IEquipment_H

#include "pch_extream.h"

#include "GameElement.h"

class IEquipment {
public:
    virtual void setPosition(const glm::vec2 position) = 0;
    virtual std::shared_ptr<GameElement> GetGameObject() const = 0;

    //    virtual GameElement getWindowObject() = 0;
    //    virtual GameElement getItemObject() = 0;
};

#endif // FUCK_PTSD_IEquipment_H
