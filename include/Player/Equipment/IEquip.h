//
// Created by adven on 2024/4/28.
//

#ifndef FUCK_PTSD_IEQUIP_HPP
#define FUCK_PTSD_IEQUIP_HPP

#include <GameElement.h>

class IEquip : public GameElement {
public:
    enum Pos { COL = 0, ROW };

    virtual std::string GetName() const = 0;

    virtual std::string GetType() const = 0;
};

#endif  // FUCK_PTSD_IEQUIP_HPP
