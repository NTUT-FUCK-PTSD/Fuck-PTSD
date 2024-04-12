//
// Created by 陳世昂 on 2024/3/25.
//

#include "Player/Items/Heart.h"

Heart::Heart() {

    resetHP();
}

std::vector<std::shared_ptr<Util::GameObject>> Heart::getGameObjects() const {
    return {m_OneHeart, m_TwoHeart, m_ThreeHeart};
}

std::shared_ptr<GameElement> Heart::GetGameObject() const {
    m_Heart->SetVisible(false);
    return m_Heart;
}

void Heart::gainHeart(const size_t number) {
    size_t HP = m_MaxHp + 2 * number;
    if (HP > 20) {
        LOG_ERROR("the value `m_MaxHP` only in range 1 ~ 20");
        return;
    }

    for (size_t i = m_MaxHp / 2; i < HP / 2; i++) {
        m_ElementList.push_front(generalHeart(
            STATE::EMPTY, m_FirstPosition + m_eachPositionDiff_X * float(i)));
        m_Heart->AddChild(m_ElementList.front());

        if (m_ElementList.size() > 5) {
            for (size_t j = 0; j < 5; j++) {
                m_ElementList[j]->SetPivot(glm::vec2(-(26 + 2.0f / 3.0f), 0) *
                                           float(m_ElementList.size() - 5));
            }
            m_ElementList[5]->SetPosition(m_ElementList[5]->GetPosition() +
                                          m_eachPositionDiff_Y);
            m_ElementList[5]->SetPivot({0, 0});
        }
    }

    m_MaxHp = HP;
    UpdateHP();
}

void Heart::resetHP() {
    auto HP = m_MaxHp / 2;
    m_MaxHp = 0;

    gainHeart(HP);

    m_currentHP = m_MaxHp;
    UpdateHP();
}

std::shared_ptr<GameElement> Heart::generalHeart(Heart::STATE state,
                                                 const glm::vec2 &position) {

    const auto resultObject = std::make_shared<GameElement>();

    if (state == Heart::STATE::FULL) {
        resultObject->SetDrawable(m_FullHPImage);
    }
    else if (state == Heart::STATE::HALF) {
        resultObject->SetDrawable(m_HalfHPImage);
    }
    else if (state == Heart::STATE::EMPTY) {
        resultObject->SetDrawable(m_EmptyHPImage);
    }
    else {
        LOG_ERROR("the state that params is not available");
        return nullptr;
    }

    resultObject->SetScale(m_Scale);
    resultObject->SetPosition(position);

    return resultObject;
}

void Heart::UpdateHP() {
    for (int i = m_ElementList.size() - 1; i >= 0; i--) {
        if (int(m_currentHP) - int(i << 1) <= 0) {
            m_ElementList[i]->SetDrawable(m_EmptyHPImage);
        }
        else if (m_currentHP - (i << 1) == 1) {
            m_ElementList[i]->SetDrawable(m_HalfHPImage);
        }
        else {
            m_ElementList[i]->SetDrawable(m_FullHPImage);
        }
    }
}

void Heart::minusHP(const size_t number) {
    if (number > m_currentHP) {
        LOG_ERROR("the value of number is not available");
        return;
    }
    m_currentHP -= number;
    UpdateHP();
}

void Heart::minusHeart(const float number) {
    if (number < 0) {
        LOG_ERROR("the value of number is not available");
        return;
    }

    minusHP(number * 2);
}
