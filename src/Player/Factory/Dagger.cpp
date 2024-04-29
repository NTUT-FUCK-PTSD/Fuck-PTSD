//
// Created by 陳世昂 on 2024/4/29.
//

#include "Produce/Dagger.h"
#include <memory>
#include "Helper.hpp"
#include "Player/Player_Config.h"
#include "SpriteSheet.hpp"
#include "UGameElement.h"
#include "Util/SpriteSheet.hpp"

Dagger::Dagger() {
    GenItem();
    GenSlot();

    SetVisible(false);
}

void Dagger::SetPosition(const glm::vec2& Position) {
    this->m_Transform.translation = Position;

    const auto& list = GetChildren();
    list[0]->m_Transform.translation = Position + glm::vec2{0, -5};
    list[1]->m_Transform.translation = Position + glm::vec2{0, 0.4};
}

void Dagger::GenItem() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& size = Settings::Helper::CountImgPixel(
        Players::Config::IMAGE_DAGGER.data(),
        1,
        2
    );
    const auto& item = std::make_shared<SpriteSheet>(
        Players::Config::IMAGE_DAGGER.data(),
        size,
        std::vector<std::size_t>{0},
        false,
        100,
        true,
        100
    );

    obj->SetDrawable(item);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS);

    AddChild(obj);
}

void Dagger::GenSlot() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& slot = std::make_shared<Util::SpriteSheet>(
        Players::Config::IMAGE_SLOT_DAGGER.data()
    );

    slot->SetDrawRect(SDL_Rect{0, 0, 30, 33});
    obj->SetDrawable(slot);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetPosition(Players::Config::VAL_INITPOS);
    obj->SetScale(Players::Config::VAL_SCALE);

    AddChild(obj);
}
