//
// Created by adven on 2024/3/24.
//
//
// Created by adven on 2024/3/24.
//

#include "pch_extream.h"

#include "Player/Equipment/Throw.h"

Throw::Throw() {
    //    const auto ItemImage = std::make_shared<Util::Image>(m_ImagePathItem);

    GenWin();
    GenItem();
    GeneralLowerText();
    GeneralUpperText();

    m_Throw->SetVisible(false);
};

void Throw::GenWin() {
    m_NormalSlot = std::make_shared<Util::Image>(m_ImagePathWindow);
    m_ThrowSlot = std::make_shared<Util::Image>(m_ImagePathThrow);
    m_Window->SetDrawable(m_NormalSlot);
    m_Window->SetZIndex(m_ZIndex + 1);
    m_Window->SetScale(m_Scale);
    m_Window->SetPosition(m_Position);

    m_Throw->AddChild(m_Window);
}

void Throw::GenItem() {
    const auto ItemSize = ToolBoxs::CountImagePixel(m_ImagePathItem, 1, 2);

    const auto ItemImage = std::make_shared<SpriteSheet>(
        m_ImagePathItem,
        ItemSize,
        std::vector<std::size_t>{0},
        false,
        100,
        true,
        100
    );
    m_Item->SetDrawable(ItemImage);
    m_Item->SetZIndex(m_ZIndex);
    m_Item->SetScale(m_Scale);
    m_Item->SetPosition({m_Position.x, m_Position.y + 5});

    m_Throw->AddChild(m_Item);
}

void Throw::GeneralUpperText() {
    const auto UpperTextObject = std::make_shared<Util::Text>(
        m_TextStylePath,
        m_FontSize,
        m_Content,
        m_FontColor
    );

    m_UpperText->SetDrawable(UpperTextObject);
    m_UpperText->SetZIndex(m_ZIndex);
    m_UpperText->SetScale(m_Scale);
    m_UpperText->SetPosition(m_Position);

    m_Throw->AddChild(m_UpperText);
}

void Throw::GeneralLowerText() {
    const auto LowerTextObject = std::make_shared<Util::Text>(
        m_TextStylePath,
        m_FontSize,
        "DOWN",
        m_FontColor
    );

    m_LowerText->SetDrawable(LowerTextObject);
    m_LowerText->SetPosition(m_Position);
    m_LowerText->SetZIndex(m_ZIndex);
    m_LowerText->SetScale(m_Scale);

    m_Throw->AddChild(m_LowerText);
}

void Throw::setPosition(const glm::vec2 position) {
    m_Window->SetPosition(position);
    m_Item->SetPosition({position.x, position.y + 5});
    m_UpperText->SetPosition({position.x + 30, position.y - 40});
    m_LowerText->SetPosition({position.x + 27, position.y - 60});
}

std::shared_ptr<GameElement> Throw::GetGameObject() const {
    return m_Throw;
}

void Throw::PrepareThrowOut(bool state) {
    if (!state) {
        m_LowerText->SetVisible(true);
        m_UpperText->SetVisible(true);

        m_Window->SetDrawable(m_NormalSlot);
        return;
    }

    m_LowerText->SetVisible(false);
    m_UpperText->SetVisible(false);

    m_Window->SetDrawable(m_ThrowSlot);
}
