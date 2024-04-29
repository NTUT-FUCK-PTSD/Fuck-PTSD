//
// Created by 陳世昂 on 2024/4/29.
//

#ifndef FUCK_PTSD_2024_4_29_DAGGER_H
#define FUCK_PTSD_2024_4_29_DAGGER_H

#include "IEquip.h"
class Dagger : public IEquip {
public:
    explicit Dagger() = default;
    virtual ~Dagger() = default;

    [[nodiscard]]
    std::string GetName() const override {
        return "WEAPON";
    };

    [[nodiscard]]
    std::string GetType() const override {
        return "Dagger";
    }

private:
    void GenSlot();
    void GenItem();
};
#endif  // FUCK_PTSD_2024_4_29_DAGGER_H
