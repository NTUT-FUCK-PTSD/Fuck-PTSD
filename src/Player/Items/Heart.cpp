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

void Heart::rendererHeart() {
    for (auto element : m_ElementList) {
        m_Heart->AddChild(element);
    }
}

void Heart::gainHeart(const size_t &number) {
    auto HP = m_MaxHp + 2 * number;
    if (HP > 20) {
        LOG_ERROR("the value `m_MaxHP` only in range 1 ~ 20");
        return;
    }

    float times_X = m_MaxHp > 10 ? (m_MaxHp - 10) / 2 : m_MaxHp / 2;
    float times_Y = m_MaxHp > 10 ? 1 : 0;
    glm::vec2 Initposition = m_FirstPosition + m_eachPositionDiff_Y * times_Y +
                             m_eachPositionDiff_X * times_X;
    LOG_INFO(Initposition);
    for (std::size_t i = m_MaxHp / 2; i < std::size_t(HP / 2); i++) {

        const auto heart = generalHeart(FULL, Initposition);
        m_ElementList.push_back(heart);

        Initposition += m_eachPositionDiff_X;
        if (i == 4) {
            Initposition = m_FirstPosition + m_eachPositionDiff_Y;
        }
    }
    m_MaxHp = HP;
}

void Heart::resetHP() {
    auto HP = m_MaxHp / 2;
    m_MaxHp = 0;

    gainHeart(HP);

    m_currentHP = m_MaxHp;
    rendererHeart();
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

void Heart::minusHP(const size_t &number) {
    if (number > m_currentHP) {
        LOG_ERROR("the value of number is not available");
        return;
    }
    m_currentHP -= number;

    std::size_t i = 0;
    // renderer the full heart

    for (; i < std::size_t(m_currentHP / 2); i++) {
        m_ElementList[i]->SetDrawable(m_FullHPImage);
    }

    // render the half heart
    if (m_currentHP % 2 != 0) {
        m_ElementList[i]->SetDrawable(m_HalfHPImage);
        i++;
    }

    for (; i < std::size_t(m_MaxHp); i++) {
        m_ElementList[i]->SetDrawable(m_EmptyHPImage);
    }
}

void Heart::minusHeart(const float &number) {
    if (number < 0) {
        LOG_ERROR("the value of number is not available");
        return;
    }

    minusHP(number * 2);
}
