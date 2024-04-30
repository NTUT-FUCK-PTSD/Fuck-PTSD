//
// Created by 陳世昂 on 2024/4/29.
//

#ifndef FUCK_PTSD_2024_4_29_BOMB_H
#define FUCK_PTSD_2024_4_29_BOMB_H

#include <string_view>
#include "IEquip.h"

class Bomb : public IEquip {
public:
    explicit Bomb(std::size_t number);
    virtual ~Bomb() = default;

    void SetPosition(const glm::vec2& Position) override;

    [[nodiscard]]
    Pos GetWinPos() const override {
        return Pos::COL;
    }

    [[nodiscard]]
    std::string GetName() const override {
        return std::string(m_Name.begin(), m_Name.end());
    }

    [[nodiscard]]
    std::string GetType() const override {
        return "1";
    }

private:
    void GenSlot();
    void GenItem();
    void GenFirstTextLine();
    void GenSecondTextLine();

    static constexpr std::string_view m_Name = "BOMB";

    static constexpr std::string_view m_FirstTxt = "DOWN";

    static constexpr std::string_view m_SecondTxt = "LEFT";

    static constexpr glm::vec2 m_SlotOffset = {0, 0};

    static constexpr glm::vec2 m_ItemOffset = {0, 10};

private:
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
    std::size_t m_Number = 1;
};

#endif  // FUCK_PTSD_2024_4_29_BOMB_H
