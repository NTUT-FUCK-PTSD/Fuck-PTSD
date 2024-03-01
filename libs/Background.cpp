//
// Created by adven on 2024/3/1.
//
#include "Background.hpp"

#include "Util/Image.hpp"

Background::Background(const std::string& ImagePath) {
    SetImage(ImagePath);
}

void Background::SetImage(const std::string& ImagePath) {
    this->m_ImagePath = ImagePath;

    this->m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
