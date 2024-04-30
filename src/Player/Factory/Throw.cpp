#include "Game/Warehouse/Throw.h"

#include <memory>
#include <stdexcept>
#include "Game_config.h"
#include "Helper.hpp"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"
#include "UGameElement.h"
#include "Util/Image.hpp"

#include "exception"

Game::Warehouse::Throw::Throw(std::string filePath) {
    m_ItemImg = filePath;

    GenSlot();
    GenSlot2();
    GenItem();
    GenFirstTxt();
    GenSecondTxt();

    InitSlot();
    SetVisible(false);
}

void Game::Warehouse::Throw::SpecialFunction(Config::SF sf) {
    switch (sf) {
    case Config::SF::INIT: InitSlot(); break;
    case Game::Config::SF::FIRST: ToggleSlot(); break;
    default: throw std::runtime_error("no type in throw.cpp");
    }
}

void Game::Warehouse::Throw::InitSlot() {
    const auto& list = GetChildren();

    list[0]->SetVisible(true);
    list[1]->SetVisible(false);
    list[2]->SetVisible(true);
    list[3]->SetVisible(true);
    list[4]->SetVisible(true);
}

void Game::Warehouse::Throw::ToggleSlot() {
    const auto& list = GetChildren();

    list[0]->SetVisible(false);
    list[1]->SetVisible(true);
    list[2]->SetVisible(true);
    list[3]->SetVisible(true);
    list[4]->SetVisible(true);
}

void Game::Warehouse::Throw::SetPosition(const glm::vec2& Position) {
    this->m_Transform.translation = Position;

    const auto& list = GetChildren();
    list[0]->m_Transform.translation = Position + m_SlotOffset;
    list[1]->m_Transform.translation = Position + m_SlotOffset;
    list[2]->m_Transform.translation = Position + m_ItemOffset;
    list[3]->m_Transform.translation = Position + m_FirstTxtOffset;
    list[4]->m_Transform.translation = Position + m_SecondTxtOffset;
}

void Game::Warehouse::Throw::GenSlot() {
    const auto& obj = std::make_shared<Util::GameElement>();

    const auto& item = std::make_shared<Util::Image>(
        Players::Config::IMAGE_SLOT_THROW.data()
        );

    obj->SetDrawable(item);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS);

    AddChild(obj);
}

void Game::Warehouse::Throw::GenSlot2() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& size = Settings::Helper::CountImgPixel(
        Players::Config::IMAGE_SLOT_THROW2.data(),
        1,
        2
    );

    const auto& item = std::make_shared<Util::Image>(
        Players::Config::IMAGE_SLOT_THROW2.data()
        );

    obj->SetDrawable(item);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS);

    AddChild(obj);
}

void Game::Warehouse::Throw::GenItem() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& size = Settings::Helper::CountImgPixel(m_ItemImg, 1, 2);

    const auto& item = std::make_shared<SpriteSheet>(
        m_ItemImg,
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

void Game::Warehouse::Throw::GenFirstTxt() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& item = std::make_shared<Util::Text>(
        Players::Config::STY_FONT.data(),
        Players::Config::VAL_FONT_SIZE,
        static_cast<std::string>(m_FistTxt),        Players::Config::VAL_COLOR_WHITE
    );

    obj->SetDrawable(item);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS);

    AddChild(obj);
}

void Game::Warehouse::Throw::GenSecondTxt() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& item = std::make_shared<Util::Text>(
        Players::Config::STY_FONT.data(),
        Players::Config::VAL_FONT_SIZE,
        static_cast<std::string>(m_SecondTxt),        Players::Config::VAL_COLOR_WHITE
    );

    obj->SetDrawable(item);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale(Players::Config::VAL_SCALE);
    obj->SetPosition(Players::Config::VAL_INITPOS);

    AddChild(obj);
}
