//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_EQUIPMENT_H
#define FUCK_PTSD_EQUIPMENT_H

#include "pch_extream.h"

#include "GameElement.h"

class Equipment {
public:
    virtual std::shared_ptr<GameElement> getGameElement() = 0;

    virtual void setPosition(const glm::vec2 position) = 0;

    virtual std::vector<std::shared_ptr<Util::GameObject>> getGameObjects() = 0;


//    virtual GameElement getWindowObject() = 0;
//    virtual GameElement getItemObject() = 0;

};

#endif // FUCK_PTSD_EQUIPMENT_H
