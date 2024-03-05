//
// Created by adven on 2024/3/4.
//

#include "MainCharacter.h"
#include "SpriteSheet.hpp"
#include "Util/Image.hpp"

MainCharacter::MainCharacter() {

    glm::vec2 HeadImageSize = Util::Image(this->HeadImagePath).GetSize();
    glm::vec2 BodyImageSize = Util::Image(this->BodyImagePath).GetSize();

    const double HeadImageWidth = HeadImageSize[0];
    const double HeadImageHeight = HeadImageSize[1];

    const double EachHeadImageWidth = 4;
    const double EachHeadImageHeight = 2;

    const double BodyImageWidth = BodyImageSize[0];
    const double BodyImageHeight = BodyImageSize[1];

    const double EachBodyImageWidth = 4;
    const double EachBodyImageHeight = 10;

    auto HeadImage = std::make_shared<SpriteSheet>(
        this->HeadImagePath,
        glm::vec2(HeadImageWidth / EachHeadImageWidth,
                  HeadImageHeight / EachHeadImageHeight),
        std::vector<std::size_t>{0, 1, 2, 3}, true, 100, true, 100);

    auto BodyImage = std::make_shared<SpriteSheet>(
        this->BodyImagePath,
        glm::vec2(BodyImageWidth / EachBodyImageWidth,
                  BodyImageHeight / EachBodyImageHeight),
        std::vector<std::size_t>{0, 1, 2, 3}, true, 100, true, 100);

    m_Body->SetDrawable(BodyImage);
    m_MainCharacter->SetDrawable(HeadImage);

    m_Body->SetPosition(InitPosition);
    m_MainCharacter->SetPosition(InitPosition);

    m_Body->SetZIndex(ZIndex);
    m_MainCharacter->SetZIndex(ZIndex);
    m_Body->SetScale({3, 3});

    m_MainCharacter->AddChild(m_Body);
    m_MainCharacter->SetScale({3, 3});
}

void MainCharacter::Render(Util::Root &m_Render) {
    m_Render.AddChild(m_MainCharacter);
}
