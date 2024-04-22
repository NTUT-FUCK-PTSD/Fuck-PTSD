//
// Created by adven on 2024/3/24.
//

#include "pch_extream.h"

#include "Player/Equipment/Weapon.h"

Weapon::Weapon(WeaponEnum::Type type) {
    // renderer the window
    rendererWindow();

    // renderer the item
    selectWeaponType(type);
    rendererItem();

    m_Attack->SetVisible(false);
}

void Weapon::selectWeaponType(WeaponEnum::Type type) {
    switch (type) {
    case WeaponEnum::Type::DAGGER:
        m_ItemType = std::make_shared<ToolSystem::EntityDagger>();
        break;
    case WeaponEnum::Type::BROADSWORD:
        m_ItemType = std::make_shared<ToolSystem::EntityBroadsword>();
        break;
    case WeaponEnum::Type::RAPIER:
        m_ItemType = std::make_shared<ToolSystem::EntityRapier>();
        break;
    }

    m_ImagePathItem = m_ItemType->imagePath;
}

void Weapon::rendererWindow() {
    const auto WindowSpriteSheet = std::make_shared<Util::SpriteSheet>(
        m_ImagePathWindow
    );

    WindowSpriteSheet->SetDrawRect(SDL_Rect{0, 0, 30, 33});
    //    const auto WindowImage =
    //    std::make_shared<Util::Image>(m_ImagePathWindow);

    //    m_Window->SetDrawable(WindowImage);
    m_Window->SetDrawable(WindowSpriteSheet);
    m_Window->SetZIndex(m_ZIndex + 1);
    m_Window->SetScale(m_Scale);
    m_Window->SetPosition(m_Position);
    m_Attack->AddChild(m_Window);
}

void Weapon::rendererItem() {
    auto ItemSize = ToolBoxs::CountImagePixel(m_ImagePathItem, 1, 2);

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
    m_Item->SetPosition({m_Position.x, m_Position.y - 5});
    m_Attack->AddChild(m_Item);
}

void Weapon::setPosition(const glm::vec2 position) {
    m_Window->SetPosition({position.x, position.y + 0.4});
    m_Item->SetPosition({position.x, position.y - 5});

    m_Position = position;
}

std::shared_ptr<GameElement> Weapon::GetGameObject() const {
    return m_Attack;
}

void Weapon::setWeaponType(WeaponEnum::Type type) {
    selectWeaponType(type);
    rendererItem();
}

bool Weapon::GetIsThrow() {
    return m_ItemType->isThrow;
}
