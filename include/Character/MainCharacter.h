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
    std::string BodyImagePath = ASSETS_DIR "/entities/player1_armor_body.png";

    std::string HeadImagePath = ASSETS_DIR "/entities/player1_heads.png";
    std::shared_ptr<GameElement> m_MainCharacter =
        std::make_shared<GameElement>();

    std::shared_ptr<GameElement> m_Body = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Head = std::make_shared<GameElement>();

    glm::vec2 InitPosition = {0, 0};

    uint16_t ZIndex = 50;

public:
    explicit MainCharacter();

    void Render(Util::Root &m_Render);

    /* ---- Setter and Getter ----- */
public:
    void SetBodyImagePath(std::string &Path) { this->BodyImagePath = Path; };

    void SetHeadImagePath(std::string &Path) { this->HeadImagePath = Path; }
};

#endif // FUCK_PTSD_MAINCHARACTER_H
