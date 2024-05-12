//
// Created by adven on 2024/5/12.
//

#ifndef FUCK_PTSD_0512_FOOD_2_H
#define FUCK_PTSD_0512_FOOD_2_H

#include "Game/Warehouse/IEquip.h"

namespace Game::Warehouse {
class Food_2 final : public IEquip {
public:
    explicit Food_2();
    virtual ~Food_2() = default;

    void SetPosition(const glm::vec2& Position) override;

    [[nodiscard]]
    Pos GetWinPos() const override {
        return Pos::COL;
    }
    [[nodiscard]]
    std::string GetName() const override {
        return "ITEM";
    }
    [[nodiscard]]
    std::string GetType() const override {
        return "Food_1";
    }
    [[nodiscard]]
    std::string GetImagePath() const override {
        return "";
    }

private:
    void GenItem();
    void GenSlot();
    void GenFirstTextLine();
    void GenSecondTextLine();

    static constexpr std::string_view m_FirstTxt = "UP+";
    static constexpr std::string_view m_SecondTxt = "LEFT";

    static constexpr glm::vec2 m_SlotOffset = {0, 0};
    static constexpr glm::vec2 m_ItemOffset = {0, 10};

#ifdef _WIN32
    static constexpr glm::vec2 m_FirstOffset = {25, -40};
    static constexpr glm::vec2 m_SecondOffset = {25, -60};
#elif __APPLE__
    static constexpr glm::vec2 m_FirstOffset = {15, -40};
    static constexpr glm::vec2 m_SecondOffset = {15, -60};
#else
    static constexpr glm::vec2 m_FirstOffset = {25, -40};
    static constexpr glm::vec2 m_SecondOffset = {25, -60};
#endif
};
}  // namespace Game::Warehouse
#endif  // FUCK_PTSD_0512_FOOD_2_H
