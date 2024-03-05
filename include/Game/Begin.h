//
// Created by adven on 2024/3/2.
//

#ifndef FUCK_PTSD_BEGIN_H
#define FUCK_PTSD_BEGIN_H

#include "Util/Renderer.hpp"

#include "Background.hpp"
#include <memory>

class Begin {
public:
    static void CreateBackground(Util::Renderer &m_Root,
                                 std::shared_ptr<Background> m_MainMenu,
                                 std::shared_ptr<Background> m_Continue);
    static void RemoveBackground(Util::Renderer &m_Root,
                                 std::shared_ptr<Background> m_MainMenu,
                                 std::shared_ptr<Background> m_Continue);
};

#endif // FUCK_PTSD_BEGIN_H
