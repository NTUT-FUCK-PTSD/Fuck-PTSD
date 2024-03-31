//
// Created by 陳世昂 on 2024/3/25.
//

#ifndef FUCK_PTSD_HEART_H
#define FUCK_PTSD_HEART_H

#include "GameElement.h"
#include <iostream>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Heart final {
public:
    explicit Heart();

    void plusHP(std::size_t number);

    void minusHP(int number);

    void hitHeart(std::size_t index);

    void resetHP();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>>
    getGameObjects() const;

    std::shared_ptr<GameElement> GetGameObject() const ;

private:
    void IsDead();

    // HP settings
    float MaxHp = 3.0f;
    float currentHP = 3.0f;

    // Image Settings
    const glm::vec2 m_Scale = {3, 3};
    std::shared_ptr<Util::Image> m_FullHPImage =
        std::make_shared<Util::Image>(ASSETS_DIR "/gui/heart.png");

    std::shared_ptr<Util::Image> m_HalfHPImage =
        std::make_shared<Util::Image>(ASSETS_DIR "/gui/heart_half.png");

    std::shared_ptr<Util::Image> m_EmptyHPImage =
        std::make_shared<Util::Image>(ASSETS_DIR "/gui/heart_empty.png");

    // game object
    std::shared_ptr<GameElement> m_OneHeart = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_TwoHeart = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_ThreeHeart = std::make_shared<GameElement>();

    std::shared_ptr<GameElement> m_Heart = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_HEART_H
