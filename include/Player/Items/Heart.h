//
// Created by 陳世昂 on 2024/3/25.
//

#ifndef FUCK_PTSD_HEART_H
#define FUCK_PTSD_HEART_H

#include "GameElement.h"
#include <iostream>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

class Heart final {
public:
    explicit Heart();

    void plusHP(std::size_t number);

    void minusHP(float number);

    void hitHeart(std::size_t index);

    void resetHP();

    void SetHeartMaxHp(float value);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>>
    getGameObjects() const;

    std::shared_ptr<GameElement> GetGameObject() const ;

    enum STATE {
        FULL = 0,
        HALF,
        EMPTY,
    };

private:
    void IsDead();
    std::shared_ptr<GameElement> generalHeart(STATE state, const glm::vec2 &position);
    void rendererHeart();

    // HP settings
    //
    float m_MaxHp = 6.0f;
    float m_currentHP = 6.0f;
    const glm::vec2 m_FirstPosition = {500, 350};
    const glm::vec2 m_eachPositionDiff_X = {-80, 0};
    const glm::vec2 m_eachPositionDiff_Y = {0, -80};

    // Image Settings
    const glm::vec2 m_Scale = {3, 3};
    std::shared_ptr<Util::Image> m_FullHPImage =
        std::make_shared<Util::Image>(ASSETS_DIR "/gui/heart.png");

    std::shared_ptr<Util::Image> m_HalfHPImage =
        std::make_shared<Util::Image>(ASSETS_DIR "/gui/heart_half.png");

    std::shared_ptr<Util::Image> m_EmptyHPImage =
        std::make_shared<Util::Image>(ASSETS_DIR "/gui/heart_empty.png");

    // game object
    std::vector<std::shared_ptr<GameElement>> m_ElementList;

    std::shared_ptr<GameElement> m_OneHeart = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_TwoHeart = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_ThreeHeart = std::make_shared<GameElement>();

    std::shared_ptr<GameElement> m_Heart = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_HEART_H
