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

void Heart::AddToList() {
    for (auto element : m_ElementList) {
        m_Heart->AddChild(element);
    }
}

void Heart::resetHP() {
    if (std::size_t(m_MaxHp * 10) % 10 != 0) {
        LOG_ERROR("the Heart of init value was not a integer");
        return;
    }

    m_currentHP = m_MaxHp;

    uint16_t m_Times_x =
        size_t(m_MaxHp / 5) > 0 ? 4 : std::size_t(m_MaxHp) % 5 - 1;

    glm::vec2 InitPosition = m_FirstPosition;
    InitPosition += m_eachPositionDiff_X * float(m_Times_x);

    for (std::size_t i = 1; i <= std::size_t(m_MaxHp); i++) {
        const auto heart = generalHeart(FULL, InitPosition);
        m_ElementList.push_back(heart);

        if (i % 5 == 0 && i != 0) {
            // i = 5

            // y offset
            InitPosition += m_eachPositionDiff_Y;

            // x offset
            m_Times_x =
                (size_t(m_MaxHp) - i) / 5 > 0 ? 5 : (size_t(m_MaxHp) - i) % 5;
            InitPosition += m_eachPositionDiff_X * float(m_Times_x);
        }

        InitPosition -= m_eachPositionDiff_X;
    }

    m_currentHP = m_MaxHp;
    AddToList();
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

void Heart::RendererHeart(std::size_t number) {
    std::size_t i = 0;

    // renderer the full heart
    for (; i < std::size_t(m_currentHP); i++) {
        m_ElementList[i]->SetDrawable(m_FullHPImage);
    }

    // render the half heart
    if (std::size_t(m_currentHP * 2) % 2 != 0) {
        m_ElementList[i]->SetDrawable(m_HalfHPImage);
        i++;
    }

    for (; i < m_MaxHp; i++) {
        m_ElementList[i]->SetDrawable(m_EmptyHPImage);
    }
};

void Heart::plusHP(float number) {
    if (size_t(number * 10) % 5 != 0 && size_t(number * 10) % 10 != 0) {
        LOG_ERROR("the Heart's minusHP is not value of times of 1 or 0.5.");
        return;
    }

    if (m_currentHP + number > m_MaxHp) {
        LOG_ERROR("The HP is out of limit when you plus");
        return;
    }

    m_currentHP += number;
    RendererHeart((size_t)m_currentHP);
}

void Heart::minusHP(float number) {
    if (size_t(number * 10) % 5 != 0 && size_t(number * 10) % 10 != 0) {
        LOG_ERROR("the Heart's minusHP is not value of times of 1 or 0.5.");
        return;
    }

    if (m_currentHP - number <= 0) {
        RendererHeart(0);
        m_Dead = true;
        return;
    }

    m_currentHP -= number;
    RendererHeart((size_t)m_currentHP);
}

void Heart::SetHeartMaxHp(float value) {
    if (size_t(value * 10) % 5 != 0 && size_t(value * 10) % 10 != 0) {
        LOG_ERROR("the Heart's minusHP is not value of times of 1 or 0.5.");
        return;
    }

    m_MaxHp = value;
    m_currentHP = value;
}

bool Heart::IsDead() {
    return m_Dead;
}
