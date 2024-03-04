//
// Created by adven on 2024/3/4.
//

#ifndef FUCK_PTSD_MAINCHARACTER_H
#define FUCK_PTSD_MAINCHARACTER_H

#include "Core/Drawable.hpp"
#include "GameElement.h"
#include "Util/Root.hpp"
#include <iostream>

class MainCharacter {
private:
    std::shared_ptr<GameElement> m_Body;
    std::shared_ptr<GameElement> m_Head;

    glm::vec2 InitPosition = {0, 0};

    uint16_t ZIndex = 50;

public:
    explicit MainCharacter();

    void Render(Util::Root &m_Render);
};

#endif // FUCK_PTSD_MAINCHARACTER_H
