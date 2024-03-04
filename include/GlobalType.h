//
// Created by adven on 2024/3/4.
//

#ifndef FUCK_PTSD_GLOBALTYPE_H
#define FUCK_PTSD_GLOBALTYPE_H

#include "Background.hpp"
#include <iostream>
#include <memory>

namespace GlobalType {
struct TBackground {
    std::shared_ptr<Background> m_MainMenu;
    std::shared_ptr<Background> m_Continue;
};
} // namespace GlobalType
#endif // FUCK_PTSD_GLOBALTYPE_H
