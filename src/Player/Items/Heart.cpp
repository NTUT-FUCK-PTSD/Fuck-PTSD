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

    auto position = m_FirstPosition;
    for (int i = 0; i < std::size_t(m_MaxHp); i++) {

        const auto heart = generalHeart(FULL, position);
        m_ElementList.push_back(heart);

        // heart's y position
        if ((i + 1) % 5 == 0 && i != 0) {
            position = {m_FirstPosition.x,
                        m_FirstPosition.y + m_eachPositionDiff_Y.y};
        }
        // heart's x position
        if ((i + 1) % 5 != 0 || i == 0) {
            position = position + m_eachPositionDiff_X;
        }
    }

    m_currentHP = m_MaxHp;
    rendererHeart();
    minusHP(2.5);

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

// 2.5
// 2
// 0.5
void Heart::minusHP(float number) {
    if (std::size_t(number * 2) % 1 != 0) {
        LOG_ERROR("the Heart's minusHP is not value of time of 1 or 0.5.");
        return;
    }

    m_currentHP -= number;

    std::size_t i = 0;
    // renderer the full heart
    for (i; i < std::size_t(m_currentHP); i++) {
        m_ElementList[4 - i]->SetDrawable(m_FullHPImage);
    }

    // render the half heart
    if (std::size_t(m_currentHP * 2) % 2 != 0) {
        LOG_INFO(std::size_t(m_currentHP * 2) % 2);
        m_ElementList[i]->SetDrawable(m_HalfHPImage);
        i++;
    }

    for (i; i< m_MaxHp ; i++) {
        m_ElementList[4 - i] ->SetDrawable(m_EmptyHPImage);
    }
}
