//
// Created by adven on 2024/5/2.
//

#ifndef FUCK_PTSD_SPEAR_H
#define FUCK_PTSD_SPEAR_H
#include "Game/Warehouse/IEquip.h"

class Spear : public IEquip {
public:
    explicit Spear();
    ~Spear() = default;

    void SetPosition(const glm::vec2& Position) override;

    [[nodiscard]]
    Pos GetWinPos() const override {
        return Pos::ROW;
    }

    [[nodiscard]]
    std::string GetName() const override {
        return "WEAPON";
    };

    [[nodiscard]]
    std::string GetType() const override {
        return "Spear";
    }

    [[nodiscard]]
    std::string GetImagePath() const override {
        return ASSETS_DIR
            "/items/weapon_spear.png";
    }

private:
    void GenSlot();
    void GenItem();
};

#endif  // FUCK_PTSD_SPEAR_H
