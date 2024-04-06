//
// Created by adven on 2024/3/24.
//

#include "pch_extream.h"

#include "Player/Items/Tools.h"

Tools::Tools() {
    // create tool Throw
    SetThrow();

    // create tool bomb
    SetBomb();

    // create tool shovel
    SetShovel();

    // create tool Weapon
    SetWeapon();

    rearrangeCol();
    rearrangeRow();
}

void Tools::SetThrow() {
    m_colEquipList.push_back(std::make_shared<Throw>());
    m_colPosIdx.push_back(THROW);
}

void Tools::SetBomb() {
    m_colEquipList.push_back(std::make_shared<Bomb>());
    m_colPosIdx.push_back(BOMB);
}

void Tools::SetShovel() {
    m_rowEquipList.push_back(std::make_shared<Shovel>());
    m_rowPosIdx.push_back(SHOVEL);
}

void Tools::SetWeapon() {
    auto w = std::make_shared<Weapon>();
    m_rowEquipList.push_back(w);
    m_rowPosIdx.push_back(WEAPON);

    if (!w->GetIsThrow()) {
        RemoveThrow();
    }
}

void Tools::RemoveThrow() {
    auto f = distance(m_colPosIdx.begin(), find(m_colPosIdx.begin(), m_colPosIdx.end(), THROW));
    m_colPosIdx.erase(m_colPosIdx.begin() + f);
    m_colEquipList.erase(m_colEquipList.begin() + f);

    rearrangeCol();
}

void Tools::RemoveBomb() {
    auto f = distance(m_colPosIdx.begin(), find(m_colPosIdx.begin(), m_colPosIdx.end(), BOMB));
    m_colPosIdx.erase(m_colPosIdx.begin() + f);
    m_colEquipList.erase(m_colEquipList.begin() + f);

    rearrangeCol();
}

void Tools::RemoveShovel() {
    auto f = distance(m_rowPosIdx.begin(), find(m_rowPosIdx.begin(), m_rowPosIdx.end(), SHOVEL));
    m_rowPosIdx.erase(m_rowPosIdx.begin() + f);
    m_rowEquipList.erase(m_rowEquipList.begin() + f);

    rearrangeRow();
}

void Tools::RemoveWeapon() {
    auto f = distance(m_rowPosIdx.begin(), find(m_rowPosIdx.begin(), m_rowPosIdx.end(), WEAPON));
    m_rowPosIdx.erase(m_rowPosIdx.begin() + f);
    m_rowEquipList.erase(m_rowEquipList.begin() + f);

    rearrangeRow();
}

std::shared_ptr<GameElement> Tools::GetGameObject() const {

    for (auto elem : m_rowEquipList) {
        m_Tools ->AddChild(elem->GetGameObject());
    }

    for (auto elem: m_colEquipList) {
        m_Tools->AddChild(elem->GetGameObject());
    }

    m_Tools->SetVisible(false);
    return m_Tools;
}

void Tools::rearrangeCol() {
    for (int i = 0; i < m_colEquipList.size() ;i++) {
        auto equipList = m_colEquipList[i];
        auto pos = m_colPosList[i];

        equipList->setPosition(pos);
    }
}

void Tools::rearrangeRow() {
    for (int i = 0; i < m_rowEquipList.size() ;i++) {
        auto equipList = m_rowEquipList[i];
        auto pos = m_rowPosList[i];

        equipList->setPosition(pos);
    }
}
