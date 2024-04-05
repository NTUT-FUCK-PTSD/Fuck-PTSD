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

void Heart::resetHP() {
    if (std::size_t(m_MaxHp * 10) % 10 != 0) {
        LOG_ERROR("the Heart of init value was not a integer");
        return;
    }

    if (std::size_t(m_MaxHp) > 10 ) {
        LOG_ERROR("the value `m_MaxHP` only in range 1 ~ 10");
        return ;
    }

    glm::vec2 Initposition = m_FirstPosition;

    float m_Times_X = (m_MaxHp - 1) / 5 == 0 ? m_MaxHp : 4;
    Initposition = Initposition + m_eachPositionDiff_X * m_Times_X;

    for (int i = 0; i < std::size_t(m_MaxHp); i++) {

        LOG_INFO(Initposition);

        const auto heart = generalHeart(FULL, Initposition);
        m_ElementList.push_back(heart);

        if ((i + 1) % 5 == 0 && i != 0) {
            Initposition = Initposition + m_eachPositionDiff_Y;

            float m_Times_X = (i + 1) % 5 == 0 ? size_t(m_MaxHp) % 5 :(i + 1) % 5 + 1;
            Initposition = Initposition + m_eachPositionDiff_X * m_Times_X;
        }

        Initposition = Initposition - m_eachPositionDiff_X;
    }

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

void Heart::minusHP(float number) {
    if (std::size_t(number * 2) % 1 != 0) {
        LOG_ERROR("the Heart's minusHP is not value of time of 1 or 0.5.");
        return;
    }

    m_currentHP -= number;

    std::size_t i = 0;
    // renderer the full heart
    for (i; i < std::size_t(m_currentHP); i++) {
        m_ElementList[i]->SetDrawable(m_FullHPImage);
    }

    // render the half heart
    if (std::size_t(m_currentHP * 2) % 2 != 0) {
        LOG_INFO(std::size_t(m_currentHP * 2) % 2);
        m_ElementList[i]->SetDrawable(m_HalfHPImage);
        i++;
    }

    for (i; i < m_MaxHp; i++) {
        m_ElementList[i]->SetDrawable(m_EmptyHPImage);
    }
}
