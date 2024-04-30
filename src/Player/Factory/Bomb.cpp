//
// Created by 陳世昂 on 2024/4/29.
//

#include <Settings/UGameElement.h>
#include <memory>

#include "Game/Player_Config.h"
#include "Game/Warehouse/Bomb.h"
#include "Settings/Helper.hpp"
#include "SpriteSheet.hpp"

Bomb::Bomb(std::size_t number) {
    m_Number = number;

    GenSlot();
    GenItem();
    GenFirstTextLine();
    GenSecondTextLine();

    SetVisible(false);
}

void Bomb::SetPosition(const glm::vec2& Position) {
    this->m_Transform.translation = Position;

    const auto& list = GetChildren();
    list[0]->m_Transform.translation = Position + m_SlotOffset;
    list[1]->m_Transform.translation = Position + m_ItemOffset;
    list[2]->m_Transform.translation = Position + m_FirstOffset;
    list[3]->m_Transform.translation = Position + m_SecondOffset;
}

void Bomb::GenSlot() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& slot = std::make_shared<Util::Image>(
        static_cast<std::string>(Players::Config::IMAGE_SLOT_BOMB)
    );

    obj->SetDrawable(slot);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS + m_SlotOffset);

    AddChild(obj);
}

void Bomb::GenItem() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& item = std::make_shared<SpriteSheet>(
        Players::Config::IMAGE_BOMB.data(),
        ToolBoxs::CountImagePixel(
            static_cast<std::string>(Players::Config::IMAGE_BOMB),
            5,
            2
        ),
        std::vector<std::size_t>{0, 1, 2, 3, 4},
        false,
        100,
        true,
        100
    );

    obj->SetDrawable(item);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS + m_ItemOffset);

    AddChild(obj);
}

void Bomb::GenFirstTextLine() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& text = std::make_shared<Util::Text>(
        Players::Config::STY_FONT.data(),
        Players::Config::VAL_FONT_SIZE,
        static_cast<std::string>(m_FirstTxt),
        Players::Config::VAL_COLOR_WHITE
    );

    obj->SetDrawable(text);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_FONT_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS + m_FirstOffset);

    AddChild(obj);
}

void Bomb::GenSecondTextLine() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& text = std::make_shared<Util::Text>(
        Players::Config::STY_FONT.data(),
        Players::Config::VAL_FONT_SIZE,
        static_cast<std::string>(m_SecondTxt),
        Players::Config::VAL_COLOR_WHITE
    );

    obj->SetDrawable(text);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_FONT_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS + m_SecondOffset);

    AddChild(obj);
}
