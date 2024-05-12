//
// Created by adven on 2024/5/12.
//

#ifndef FUCK_PTSD_Graphs_COIN_H
#define FUCK_PTSD_Graphs_COIN_H

#include "Dungeon/Map.h"

namespace Game::Graphs {
class Coin final : public Dungeon::Item {
public:
    explicit Coin(std::size_t number);
    virtual ~Coin() = default;

    std::size_t GetNumber();

    std::string GetClassName() override { return "Coin"; }

private:
    std::size_t m_Number = 0;

    static const std::vector<std::string_view> m_CoinList;
};
}  // namespace Game::Graphs

#endif  // FUCK_PTSD_Graphs_COIN_H
