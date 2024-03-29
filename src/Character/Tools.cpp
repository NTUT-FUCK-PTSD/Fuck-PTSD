//
// Created by adven on 2024/3/24.
//

#include "pch_extream.h"

#include "Tools.h"

Tools::Tools() {

    // create tool shovel
    m_Shovel = std::make_shared<Shovel>();
    m_Shovel->setPosition(m_ShovelPosition);

    // create tool Weapon
    m_Attack = std::make_shared<Weapon>();
    m_Attack->setPosition(m_AttackPosition);

    // create tool Throw
    m_Throw = std::make_shared<Throw>();
    m_Throw->setPosition(m_ThrowPosition);

    // create tool bomb
    m_Bomb = std::make_shared<Bomb>();
    m_Bomb->setPosition(m_BombPosition);
}

std::shared_ptr<Util::GameObject> Tools::getGameObject() {
    m_Tools->AddChild(m_Shovel->getGameElement());

    m_Tools->SetVisible(true);
    return m_Tools;
}
std::vector<std::shared_ptr<Util::GameObject>> Tools::getGameObjects() {
    auto s = m_Shovel->getGameObjects();
    auto a = m_Attack->getGameObjects();
    auto t = m_Throw->getGameObjects();
    auto b = m_Bomb->getGameObjects();

    for (size_t i = 0; i < s.size(); i++) {
        m_TempGameObejct.push_back(s[i]);
    }
    for (size_t i = 0; i < a.size(); i++) {
        m_TempGameObejct.push_back(a[i]);
    }
    for (size_t i = 0; i < t.size(); i++) {
        m_TempGameObejct.push_back(t[i]);
    }
    for (size_t i = 0; i < b.size(); i++) {
        m_TempGameObejct.push_back(b[i]);
    }

    return m_TempGameObejct;
}
