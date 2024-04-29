//
// Created by 陳世昂 on 2024/4/29.
//

#ifndef FUCK_PTSD_2024_4_29_BOMB_H
#define FUCK_PTSD_2024_4_29_BOMB_H

#include "IEquip.h"

class Bomb : public IEquip {
public:
    explicit Bomb(std::size_t number);
    virtual ~Bomb() = default;

    [[nodiscard]]
    std::string GetName() const override {
        return std::string(m_Name.begin(), m_Name.end());
    }

    std::string GetType() const override { return "1"; }

private:
    void GenSlot();
    void GenItem();
    void GenFirstTextLine();
    void GenSecondTextLine();

    static constexpr std::string_view m_Name = "BOMB";
};

#endif  // FUCK_PTSD_2024_4_29_BOMB_H
