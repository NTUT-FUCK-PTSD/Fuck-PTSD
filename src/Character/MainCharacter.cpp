//
// Created by adven on 2024/3/4.
//

#include "MainCharacter.h"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"
#include "Util/Image.hpp"

MainCharacter::MainCharacter() {

    const auto HeadSize = ToolBoxs::CountImagePixel(m_HeadImagePath, 4, 2);
    const auto BodySize = ToolBoxs::CountImagePixel(m_BodyImagePath, 4, 10);

    const auto HeadImage = std::make_shared<SpriteSheet>(
        m_HeadImagePath, HeadSize, std::vector<std::size_t>{0, 1, 2, 3},
        true, 100, true, 100);

    const auto BodyImage = std::make_shared<SpriteSheet>(
        m_BodyImagePath, BodySize, std::vector<std::size_t>{0, 1, 2, 3},
        true, 100, true, 100);

    m_Body->SetDrawable(BodyImage);
    m_Body->SetPosition(InitPosition);
    m_Body->SetZIndex(ZIndex);
    m_Body->SetScale({3, 3});

    m_Head->SetDrawable(HeadImage);
    m_Head->SetPosition(InitPosition);
    m_Head->SetZIndex(ZIndex);
    m_Head->AddChild(m_Body);
    m_Head->SetScale({3, 3});

    m_MainGameObject->SetVisible(false);
    m_MainGameObject->AddChild(m_Body);
    m_MainGameObject->AddChild(m_Head);
}
