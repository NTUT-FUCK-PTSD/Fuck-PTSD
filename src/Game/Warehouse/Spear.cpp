//
// Created by adven on 2024/5/2.
//

#include "Game/Warehouse/Spear.h"
#include "Player_config.h"
#include "Settings/Helper.hpp"

Spear::Spear() {
    GenItem();
    GenSlot();

    SetVisible(false);
}

void Spear::SetPosition(const glm::vec2& Position) {
    m_Transform.translation = Position;

    const auto& list = GetChildren();
    list[0]->m_Transform.translation = Position + glm::vec2{0, -5};
    list[1]->m_Transform.translation = Position + glm::vec2{0, 0.4};
}

// std::string Spear::GetImagePath() const {
//     return Players::Config::IMAGE_SPEAR.data();
// }

void Spear::GenItem() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& size = Settings::Helper::CountImgPixel(
        Players::Config::IMAGE_SPEAR.data(),
        1,
        2
    );
    const auto& item = std::make_shared<SpriteSheet>(
        Players::Config::IMAGE_SPEAR.data(),
        size,
        std::vector<std::size_t>{0},
        false,
        100,
        true,
        100
    );

    obj->SetDrawable(item);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Window::GetScale());
    obj->SetPosition(Players::Config::VAL_INITPOS);

    AddChild(obj);
}

void Spear::GenSlot() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& slot = std::make_shared<Util::SpriteSheet>(
        Players::Config::IMAGE_SLOT_ATTACK.data()
    );

    slot->SetDrawRect(SDL_Rect{0, 0, 30, 33});
    obj->SetDrawable(slot);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetPosition(Players::Config::VAL_INITPOS);
    obj->SetScale(Window::GetScale());

    AddChild(obj);
}
