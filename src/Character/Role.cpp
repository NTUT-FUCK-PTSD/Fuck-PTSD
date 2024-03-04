//
// Created by adven on 2024/3/4.
//

#include "Role.h"
#include <iostream>

Role::Role() {}

void Role::SetDisplay(std::shared_ptr<Core::Drawable> &m_Drawable) {
    this->SetDrawable(m_Drawable);
}