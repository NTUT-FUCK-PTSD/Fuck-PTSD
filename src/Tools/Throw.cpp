//
// Created by adven on 2024/3/24.
//
//
// Created by adven on 2024/3/24.
//

#include "pch_extream.h"

#include "Throw.h"

Throw::Throw() {
    //    const auto ItemImage = std::make_shared<Util::Image>(m_ImagePathItem);
    const auto ItemSize = ToolBoxs::CountImagePixel(m_ImagePathItem, 1, 2);

    const auto ItemImage = std::make_shared<SpriteSheet>(
        m_ImagePathItem, ItemSize, std::vector<std::size_t>{0}, false, 100, true, 100
    );
    const auto WindowImage = std::make_shared<Util::Image>(m_ImagePathWindow);

    m_Window->SetDrawable(WindowImage);
    m_Item->SetDrawable(ItemImage);

    m_Window->SetZIndex(m_ZIndex + 1);
    m_Item->SetZIndex(m_ZIndex);

    m_Window->SetScale(m_Scale);
    m_Item->SetScale(m_Scale);

    m_Window->SetPosition(m_Position);
    m_Item->SetPosition({m_Position.x,m_Position.y - 10});

    m_Throw->AddChild(m_Window);
    m_Throw->AddChild(m_Item);

    m_Throw->SetVisible(true);
};

void Throw::setPosition(const glm::vec2 position) {
    m_Window->SetPosition(position);
    m_Item->SetPosition({position.x,position.y + 5});
}

std::shared_ptr<GameElement> Throw::getGameElement() {
    return m_Throw;
}
std::vector<std::shared_ptr<Util::GameObject>> Throw::getGameObjects() {
    return {m_Window, m_Item};
}
