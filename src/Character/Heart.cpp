//
// Created by 陳世昂 on 2024/3/25.
//

#include "Heart.h"
Heart::Heart() {
    m_OneHeart->SetDrawable(m_FullHPImage);
    m_TwoHeart->SetDrawable(m_FullHPImage);
    m_ThreeHeart->SetDrawable(m_FullHPImage);

    m_OneHeart->SetScale(m_Scale);
    m_TwoHeart->SetScale(m_Scale);
    m_ThreeHeart->SetScale(m_Scale);

    m_OneHeart->SetPosition({500, 350});
    m_TwoHeart->SetPosition({420, 350});
    m_ThreeHeart->SetPosition({340, 350});
}

std::vector<std::shared_ptr<Util::GameObject>> Heart::getGameObjects() const {
    return {m_OneHeart, m_TwoHeart, m_ThreeHeart};
}
