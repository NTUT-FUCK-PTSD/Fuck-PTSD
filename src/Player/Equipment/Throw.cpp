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
    const auto ItemSize = ToolBoxs::CountImagePixel(m_ImagePathItem, 1, 2);

    const auto ItemImage = std::make_shared<SpriteSheet>(
        m_ImagePathItem, ItemSize, std::vector<std::size_t>{0}, false, 100, true, 100
    );
    const auto WindowImage = std::make_shared<Util::Image>(m_ImagePathWindow);
    const auto UpperTextObject = std::make_shared<Util::Text>(
        m_TextStylePath, m_FontSize, m_Content, m_FontColor
        );
    const auto LowerTextObject = std::make_shared<Util::Text>(
        m_TextStylePath, m_FontSize, "DOWN", m_FontColor
        );

    m_Window->SetDrawable(WindowImage);
    m_Item->SetDrawable(ItemImage);
    m_Text->SetDrawable(UpperTextObject);
    m_LowerText->SetDrawable(LowerTextObject);

    m_Window->SetZIndex(m_ZIndex + 1);
    m_Item->SetZIndex(m_ZIndex);
    m_Text->SetZIndex(m_ZIndex);
    m_LowerText->SetZIndex(m_ZIndex);

    m_Window->SetScale(m_Scale);
    m_Item->SetScale(m_Scale);
    m_Text->SetScale(m_Scale);
    m_LowerText->SetScale(m_Scale);

    m_Window->SetPosition(m_Position);
    m_Item->SetPosition({m_Position.x,m_Position.y + 5});
    m_Text->SetPosition(m_Position);
    m_LowerText->SetPosition(m_Position);

    m_Throw->AddChild(m_Window);
    m_Throw->AddChild(m_Item);

    m_Throw->SetVisible(true);
};

void Throw::setPosition(const glm::vec2 position) {
    m_Window->SetPosition(position);
    m_Item->SetPosition({position.x,position.y + 5});
    m_Text->SetPosition({position.x + 15, position.y - 40});
    m_LowerText->SetPosition({position.x + 15, position.y - 60});
}

std::shared_ptr<GameElement> Throw::getGameElement() {
    return m_Throw;
}
std::vector<std::shared_ptr<Util::GameObject>> Throw::getGameObjects() {
    return {m_Window, m_Item, m_Text, m_LowerText};
}
