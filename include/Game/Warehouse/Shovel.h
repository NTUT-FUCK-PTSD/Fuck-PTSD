//
// Created by 陳世昂 on 2024/4/29.
//

#ifndef FUCK_PTSD_2024_4_29_SHOVEL_H
#define FUCK_PTSD_2024_4_29_SHOVEL_H

#include "Player/Factory/IEquip.h"

class Shovel : public IEquip {
public:
    explicit Shovel();
    virtual ~Shovel() = default;

    void SetPosition(const glm::vec2& Position) override;

    [[nodiscard]]
    Pos GetWinPos() const override {
        return Pos::ROW;
    }

    std::string GetName() const override{
        return "SHOVEL";
    }

    std::string GetType() const override {
        return "Basic";
    }

private:
    void GenSlot();
    void GenItem();
};

#endif  // FUCK_PTSD_2024_4_29_SHOVEL_H
