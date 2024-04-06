

#ifndef FUCK_PTSD_TOOLS_H
#define FUCK_PTSD_TOOLS_H

#include "pch_extream.h"

#include "Player/Equipment/Bomb.h"
#include "Player/Equipment/Shovel.h"
#include "Player/Equipment/Throw.h"
#include "Player/Equipment/Weapon.h"

class Tools final {
public:
    enum Type {
        THROW = 0,
        BOMB,
        WEAPON,
        SHOVEL,
    };

    explicit Tools();

    [[nodiscard]] std::shared_ptr<GameElement> GetGameObject() const;

    // add equipment
    void SetThrow();
    void SetBomb();
    void SetWeapon();
    void SetShovel();
    void SetShovelType(ShovelEnum::Type type);
    void SetWeaponType(WeaponEnum::Type type);
    void SetThrowType();
    void SetBombType();

    // remove
    void RemoveThrow();
    void RemoveBomb();
    void RemoveWeapon();
    void RemoveShovel();

private:
    void rearrangeCol();
    void rearrangeRow();

    template <class T>
    ptrdiff_t getListIdx(std::vector<T> list, Tools::Type type);



    std::vector<Tools::Type> m_colPosIdx;
    std::vector<Tools::Type> m_rowPosIdx;
    const std::vector<glm::vec2> m_colPosList = {{-655, 210}, {-655, 70}};
    const std::vector<glm::vec2> m_rowPosList = {{-655, 350}, {-555, 350}};


    std::vector<std::shared_ptr<IEquipment>> m_colEquipList;
    std::vector<std::shared_ptr<IEquipment>> m_rowEquipList;

    std::shared_ptr<GameElement> m_Tools = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_TOOLS_H
