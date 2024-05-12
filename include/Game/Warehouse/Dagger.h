//
// Created by 陳世昂 on 2024/4/29.
//

#ifndef FUCK_PTSD_2024_4_29_DAGGER_H
#define FUCK_PTSD_2024_4_29_DAGGER_H

#include "Game/Warehouse/IEquip.h"
class Dagger : public IEquip {
public:
    explicit Dagger();
    virtual ~Dagger() = default;

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
        return "Dagger";
    }

    [[nodiscard]]
    std::string GetImagePath() const override {
      return ASSETS_DIR
            "/items/weapon_dagger.png";
    };

private:
    void GenSlot();
    void GenItem();
};
#endif  // FUCK_PTSD_2024_4_29_DAGGER_H
