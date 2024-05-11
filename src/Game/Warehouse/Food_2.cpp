//
// Created by adven on 2024/5/12.
//

#include "Game/Warehouse/Food_2.h"
#include "Player_config.h"
#include "Settings/Helper.hpp"
#include "SpriteSheet.hpp"

namespace Game::Warehouse {
Food_2::Food_2() {
    GenSlot();
    GenItem();
    GenFirstTextLine();
    GenSecondTextLine();

    SetVisible(false);
}

void Food_2::SetPosition(const glm::vec2& Position) {
    this->m_Transform.translation = Position;

    const auto& list = GetChildren();
    list[0]->m_Transform.translation = Position + m_SlotOffset;
    list[1]->m_Transform.translation = Position + m_ItemOffset;
    list[2]->m_Transform.translation = Position + m_FirstOffset;
    list[3]->m_Transform.translation = Position + m_SecondOffset;
}

void Food_2::GenSlot() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& slot = std::make_shared<Util::Image>(
        Players::Config::IMAGE_SLOT_ITEM.data()
    );

    obj->SetDrawable(slot);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS + m_SlotOffset);

    AddChild(obj);
}

void Food_2::GenItem() {
    const auto&  obj = std::make_shared<Util::GameElement>();
    const auto&& size = static_cast<glm::ivec2>(Settings::Helper::CountImgPixel(
        Players::Config::IMAGE_FOOD_2.data(),
        1,
        2
    ));
    const auto&  item = std::make_shared<Util::SpriteSheet>(
        Players::Config::IMAGE_FOOD_2.data()
    );

    item->SetDrawRect({
      0,
      0,
      size.x,
      size.y,
    });

    obj->SetDrawable(item);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS + m_ItemOffset);

    AddChild(obj);
}

void Food_2::GenFirstTextLine() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& text = std::make_shared<Util::Text>(
        Players::Config::STY_FONT.data(),
        Players::Config::VAL_FONT_SIZE,
        m_FirstTxt.data(),
        Players::Config::VAL_COLOR_WHITE
    );

    obj->SetDrawable(text);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_FONT_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS + m_FirstOffset);

    AddChild(obj);
}

void Food_2::GenSecondTextLine() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& text = std::make_shared<Util::Text>(
        Players::Config::STY_FONT.data(),
        Players::Config::VAL_FONT_SIZE,
        m_SecondTxt.data(),
        Players::Config::VAL_COLOR_WHITE
    );

    obj->SetDrawable(text);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_FONT_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS + m_SecondOffset);

    AddChild(obj);
}
}  // namespace Game::Warehouse
