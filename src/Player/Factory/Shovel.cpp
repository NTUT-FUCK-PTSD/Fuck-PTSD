
#include "Player/Produce/Shovel.h"
#include <memory>
#include <vector>
#include "Helper.hpp"
#include "Player/Player_Config.h"
#include "SpriteSheet.hpp"
#include "UGameElement.h"

Shovel::Shovel() {
    GenItem();
    GenSlot();

    SetVisible(false);
}

void Shovel::SetPosition(const glm::vec2& Position) {
    this->m_Transform.translation = Position;

    const auto& list = GetChildren();
    list[0]->m_Transform.translation = Position + glm::vec2{0, -5};
    list[1]->m_Transform.translation = Position + glm::vec2{0, 0.4};
}

void Shovel::GenSlot() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& slot = std::make_shared<Util::Image>(
        Players::Config::IMAGE_SLOT_SHOVEL.data()
    );

    obj->SetDrawable(slot);
    obj->SetPosition(Players::Config::VAL_INITPOS);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);

    AddChild(obj);
}

void Shovel::GenItem() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto  size = Settings::Helper::CountImgPixel(
        Players::Config::IMAGE_SHOVEL_BASIC.data(),
        1,
        2
    );

    const auto& item = std::make_shared<SpriteSheet>(
        Players::Config::IMAGE_SHOVEL_BASIC.data(),
        size,
        std::vector<std::size_t>{0},
        false,
        100,
        true,
        100
    );

    obj->SetDrawable(item);
    obj->SetPosition(Players::Config::VAL_INITPOS);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);

    AddChild(obj);
}
