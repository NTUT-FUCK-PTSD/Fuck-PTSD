//
// Created by 陳世昂 on 2024/5/11.
//

#ifndef FUCK_PTSD_BLACK_CHEST_H
#define FUCK_PTSD_BLACK_CHEST_H

#include "Dungeon/Item.h"

#include "Settings/Helper.hpp"

namespace Game::Graphs {
class BlackChest : public Dungeon::Item {
public:
    explicit BlackChest() {
        const auto& size = static_cast<glm::ivec2>(
            Settings::Helper::CountImgPixel(
                Players::Config::IMAGE_CHEST_BLACK.data(),
                1,
                2
            )
        );

        const auto& blackChestImage = std::make_shared<Util::SpriteSheet>(
            Players::Config::IMAGE_CHEST_BLACK.data()
        );

        blackChestImage->SetDrawRect({0, 0, size.x, size.y});
        SetDrawable(blackChestImage);
        SetZIndex(100.0f);
        m_Transform.scale = {3, 3};
    }
    virtual ~BlackChest() = default;
};
}  // namespace Game::Graphs

#endif  // FUCK_PTSD_BLACK_CHEST_H
