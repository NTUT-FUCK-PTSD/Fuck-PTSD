//
// Created by adven on 2024/3/1.
//

#ifndef FUCK_PTSD_BACKGROUND_HPP
#define FUCK_PTSD_BACKGROUND_HPP

#include <string>
#include "Util/GameObject.hpp"

class Background: public Util::GameObject {
public:
    explicit Background(const std::string& ImagePath);
    void SetImage(const std::string& ImagePath);
private:
    std::string m_ImagePath;
};

#endif // FUCK_PTSD_BACKGROUND_HPP
