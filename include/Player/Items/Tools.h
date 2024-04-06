

#ifndef FUCK_PTSD_TOOLS_H
#define FUCK_PTSD_TOOLS_H

#include "pch_extream.h"

#include "Player/Equipment/Bomb.h"
#include "Player/Equipment/Shovel.h"
#include "Player/Equipment/Throw.h"
#include "Player/Equipment/Weapon.h"

class Tools final {
public:
    explicit Tools();

    [[nodiscard]] std::shared_ptr<GameElement> GetGameObject() const;

    // eq
    void SetThrow();
    void SetBomb();
    void SetShovelType(Shovel::Type type);
    void SetAttackType();
    void SetThrowType();
    void SetBombType();

private:
    void rearrangeCol();

    std::vector<glm::vec2> m_colPosList = {{-655, 210}, {-655, 70}};

    // shovel
    std::shared_ptr<Shovel> m_Shovel;
    glm::vec2 m_ShovelPosition = {-655, 350};

    // attack
    std::shared_ptr<Weapon> m_Attack;
    glm::vec2 m_AttackPosition = {-555, 350};

    // throw
    //    std::shared_ptr<Throw> m_Throw;
    //    glm::vec2 m_ThrowPosition = {-655, 210};
    //
    //    // bomb
    //    std::shared_ptr<Bomb> m_Bomb;
    //    glm::vec2 m_BombPosition = {-655, 70};

    std::vector<std::shared_ptr<IEquipment>> m_EquipList;

    std::shared_ptr<GameElement> m_Tools = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_TOOLS_H
