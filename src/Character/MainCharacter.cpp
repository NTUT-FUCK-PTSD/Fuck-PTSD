//
// Created by adven on 2024/3/4.
//

#include "MainCharacter.h"
#include "SpriteSheet.hpp"

MainCharacter::MainCharacter() {

    auto HeadImage = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/entities/player1_armor_body.png",
        glm::vec2(24.0f, 24.0f),
        std::vector<std::size_t>{0, 1, 2, 3},
        true,
        100,
        true,
        100);

    auto BodyImage =
        std::make_shared<SpriteSheet>(ASSETS_DIR "/entities/player1_heads.png",
                                      glm::vec2(24.0f, 13.0f),
                                      std::vector<std::size_t>{0, 1, 2, 3},
                                      true,
                                      100,
                                      true,
                                      100);
    m_Body->SetDrawable(BodyImage);
    m_Head->SetDrawable(HeadImage);

    m_Body->SetPosition(InitPosition);
    m_Head->SetPosition(InitPosition);

    m_Body->SetZIndex(ZIndex);
    m_Head->SetZIndex(ZIndex);
}

void MainCharacter::Render(Util::Root &m_Render) {
    m_Render.AddChild(m_Body);
    m_Render.AddChild(m_Head);
}