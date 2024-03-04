//
// Created by adven on 2024/3/4.
//

#include "GameElement.h"
#include <iostream>

GameElement::GameElement() {
}

void GameElement::SetDisplay(std::shared_ptr<Core::Drawable> &m_Drawable) {
    this->SetDrawable(m_Drawable);
}