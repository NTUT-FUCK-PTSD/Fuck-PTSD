//
// Created by adven on 2024/3/1.
//

#ifndef FUCK_PTSD_BACKGROUND_HPP
#define FUCK_PTSD_BACKGROUND_HPP

#include "Util/GameObject.hpp"
#include <string>

class Background : public Util::GameObject {
public:
    explicit Background(const std::string &ImagePath);
    void SetPosition(const glm::vec2 &Position) {
        m_Transform.translation = Position;
    }
    void SetScale(const glm::vec2 &Ratio) { m_Transform.scale = Ratio; }
    void SetImage(const std::string &ImagePath);

private:
    std::string m_ImagePath;
};

#endif // FUCK_PTSD_BACKGROUND_HPP
