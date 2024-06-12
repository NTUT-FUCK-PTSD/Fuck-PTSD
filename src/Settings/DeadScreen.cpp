//
// Created by adven on 2024/5/12.
//

#include "DeadScreen.h"

#include "Player_config.h"
#include "Util/Text.hpp"

namespace Settings {
DeadScreen::DeadScreen() {
    GenText();

    SetVisible(false);
}

void DeadScreen::SetPosition(const glm::vec2& Position) {
    this->m_Transform.translation = Position;

    const auto& list = GetChildren();
    list[0]->m_Transform.translation = Position;
}

void DeadScreen::GenText() {
    const auto& obj = std::make_shared<Util::GameElement>();
    const auto& text = std::make_shared<Util::Text>(
        ASSETS_DIR "/font/necrosans-18/necrosans-18.otf",
        18,
        m_Context.data(),
        Players::Config::VAL_COLOR_WHITE
    );

    obj->SetDrawable(text);
    obj->SetZIndex(Players::Config::VAL_ZINDEX);
    obj->SetScale({2, 2});
    obj->SetPosition(Players::Config::VAL_INITPOS);

    AddChild(obj);
}

void DeadScreen::SetVisibleRecursive(const bool visible) {
    SetVisible(visible);

    for (const auto& obj : GetChildren()) {
        obj->SetVisible(visible);
    }
}
}  // namespace Settings
