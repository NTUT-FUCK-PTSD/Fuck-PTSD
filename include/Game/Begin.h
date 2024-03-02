//
// Created by adven on 2024/3/2.
//

#ifndef FUCK_PTSD_BEGIN_H
#define FUCK_PTSD_BEGIN_H

#include "Util/Root.hpp"

#include <memory>
#include "Background.hpp"

class Begin {
public:
    static void CreateBackground(Util::Root& m_Root, std::shared_ptr<Background> m_MainMenu, std::shared_ptr<Background> m_Continue);
    static void RemoveBackground(Util::Root& m_Root, std::shared_ptr<Background> m_MainMenu, std::shared_ptr<Background> m_Continue);
};

#endif // FUCK_PTSD_BEGIN_H
