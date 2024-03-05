//
// Created by adven on 2024/3/4.
//

#include "MainCharacter.h"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"
#include "Util/Image.hpp"

MainCharacter::MainCharacter() {

    auto HeadSize = ToolBoxs::CountImagePixel(this->HeadImagePath, 4, 2);
    auto BodySize = ToolBoxs::CountImagePixel(this->BodyImagePath, 4, 10);

    auto HeadImage = std::make_shared<SpriteSheet>(
        this->HeadImagePath, HeadSize, std::vector<std::size_t>{0, 1, 2, 3},
        true, 100, true, 100);

    auto BodyImage = std::make_shared<SpriteSheet>(
        this->BodyImagePath, BodySize, std::vector<std::size_t>{0, 1, 2, 3},
        true, 100, true, 100);

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
