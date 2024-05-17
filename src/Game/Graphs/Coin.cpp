//
// Created by adven on 2024/5/12.
//

#include "Game/Graphs/Coin.h"
#include "Graphs_config.h"
#include "Player_config.h"
#include "Settings/Helper.hpp"

namespace Game::Graphs {
Coin::Coin(std::size_t number)
    : m_Number(number) {
    if (number >= 10) {
        throw std::runtime_error("Coin number error");
    } else if (number == 0) {
        return;
    }

    number -= 1;

    const auto& coinImagePath = m_CoinList.at(number);
    const auto& size = static_cast<glm::ivec2>(
        Settings::Helper::CountImgPixel(coinImagePath.data(), 1, 2)
    );
    const auto& coinImage = std::make_shared<Util::SpriteSheet>(
        coinImagePath.data()
    );
    coinImage->SetDrawRect({0, 0, size.x, size.y});
    SetDrawable(coinImage);
    SetZIndex(Players::Config::VAL_ZINDEX);
    m_Transform.scale = Window::GetScale();
}

std::size_t Coin::GetNumber() {
    return m_Number;
}

const std::vector<std::string_view> Coin::m_CoinList = {
  IMAGE_COIN_1,
  IMAGE_COIN_2,
  IMAGE_COIN_3,
  IMAGE_COIN_4,
  IMAGE_COIN_5,
  IMAGE_COIN_6,
  IMAGE_COIN_7,
  IMAGE_COIN_8,
  IMAGE_COIN_9,
  IMAGE_COIN_10,
};
}  // namespace Game::Graphs
