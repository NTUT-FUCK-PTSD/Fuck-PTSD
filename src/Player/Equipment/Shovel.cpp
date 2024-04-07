//
// Created by adven on 2024/3/24.
//
#include "pch_extream.h"

#include "Player/Equipment/Shovel.h"

Shovel::Shovel() {

    rendererWindow();
//    setShovelType(ShovelEnum::Type::Normal);
    m_ImagePathItem = ASSETS_DIR"/items/shovel_basic.png";
    rendererItem();
    m_Shovel->SetVisible(false);
};

void Shovel::rendererWindow() {
    const auto WindowImage = std::make_shared<Util::Image>(m_ImagePathWindow);
    m_Window->SetDrawable(WindowImage);
    m_Window->SetZIndex(m_ZIndex + 1);
    m_Window->SetScale(m_Scale);
    m_Window->SetPosition(m_Position);
    m_Shovel->AddChild(m_Window);
}

void Shovel::rendererItem() {
    const auto ItemSize = ToolBoxs::CountImagePixel(m_ImagePathItem, 1, 2);
    const auto ItemImage = std::make_shared<SpriteSheet>(
        m_ImagePathItem, ItemSize, std::vector<std::size_t>{0}, false, 100,
        true, 100);

    m_Item->SetDrawable(ItemImage);
    m_Item->SetZIndex(m_ZIndex);
    m_Item->SetScale(m_Scale);
    m_Item->SetPosition({m_Position.x, m_Position.y - 5});
    m_Shovel->AddChild(m_Item);
}

void Shovel::setPosition(const glm::vec2 position) {
    m_Window->SetPosition({position.x, position.y + 0.4});
    m_Item->SetPosition({position.x, position.y - 5});

    m_Position = position;
}

std::shared_ptr<GameElement> Shovel::GetGameObject() const {
    return m_Shovel;
}

void Shovel::setShovelType(ShovelEnum::Type type) {
    switch (type) {
    case ShovelEnum::Normal:
        m_ItemType = std::make_shared<ToolSystem::EntityShovel>();
        break;
    }

    m_ImagePathItem = m_ItemType->imagePath;
    rendererItem();
}
