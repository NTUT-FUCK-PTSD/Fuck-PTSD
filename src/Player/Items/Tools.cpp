//
// Created by adven on 2024/3/24.
//

#include "pch_extream.h"

#include "Player/Items/Tools.h"

Tools::Tools() {

    // create tool shovel
    m_Shovel = std::make_shared<Shovel>();
    m_Shovel->setPosition(m_ShovelPosition);

    // create tool Weapon
    m_Attack = std::make_shared<Weapon>();
    m_Attack->setPosition(m_AttackPosition);

    // create tool Throw
    SetThrow();

    // create tool bomb
    SetBomb();

    rearrangeCol();

    auto e = m_EquipList.begin();
    m_EquipList.erase(e+0);

    rearrangeCol();
}

void Tools::SetThrow() {
    m_EquipList.push_back(std::make_shared<Throw>());
}

void Tools::SetBomb() {
    m_EquipList.push_back(std::make_shared<Bomb>());
}


std::shared_ptr<GameElement> Tools::GetGameObject() const {
    m_Tools ->AddChild(m_Shovel->GetGameObject());
    m_Tools->AddChild(m_Attack->GetGameObject());
//    m_Tools->AddChild(m_Throw->GetGameObject());
//    m_Tools->AddChild(m_Bomb->GetGameObject());

    if (m_EquipList.empty()) {
        m_Tools->SetVisible(false);
        return m_Tools;
    }

    for (auto elem: m_EquipList) {
        m_Tools->AddChild(elem->GetGameObject());
    }

    m_Tools->SetVisible(false);
    return m_Tools;
}

void Tools::rearrangeCol() {
    for (int i = 0; i < m_EquipList.size() ;i++) {
        auto equipList = m_EquipList[i];
        auto pos = m_colPosList[i];

        equipList->setPosition(pos);
    }
}
