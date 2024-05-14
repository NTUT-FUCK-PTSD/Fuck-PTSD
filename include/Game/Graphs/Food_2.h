//
// Created by adven on 2024/5/11.
//

#ifndef FUCK_PTSD_FOOD_2_H
#define FUCK_PTSD_FOOD_2_H

#include "Dungeon/Item.h"
#include "Player_config.h"
#include "Settings/Helper.hpp"
// apple
namespace Game::Graphs {
class Food_2  : public Dungeon::Item{
public:
    explicit Food_2() {
        const auto& size = static_cast<glm::ivec2>(
            Settings::Helper::CountImgPixel(
                Players::Config::IMAGE_FOOD_2.data(),
                1,
                2
            )
        );

        const auto& blackChestImage = std::make_shared<Util::SpriteSheet>(
            Players::Config::IMAGE_FOOD_2.data()
        );

        blackChestImage->SetDrawRect({0, 0, size.x, size.y});
        SetDrawable(blackChestImage);
        SetZIndex(100.0f);
        m_Transform.scale = {3, 3};
    }

    virtual ~Food_2() = default;

    std::string GetClassName() {
        return "Food_2";
    }
};
}

#endif  // FUCK_PTSD_FOOD_2_H
