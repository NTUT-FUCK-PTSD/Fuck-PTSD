

#ifndef FUCK_PTSD_TOOLS_H
#define FUCK_PTSD_TOOLS_H

#include "pch_extream.h"

#include "Equipment.h"
#include "Shovel.h"
#include "Attack.h"
#include "Throw.h"
#include "Bomb.h"



class Tools final{
public:
    explicit Tools();

    std::shared_ptr<Util::GameObject> getGameObject();

    std::vector<std::shared_ptr<Util::GameObject>> getGameObjects();

private:
    std::vector<std::shared_ptr<Util::GameObject>> m_TempGameObejct;

    //shovel
    std::shared_ptr<Shovel> m_Shovel;
    glm::vec2 m_ShovelPosition = {-655, 350};

    //attack
    std::shared_ptr<Attack> m_Attack;
    glm::vec2 m_AttackPosition = {-555, 350};

    // throw
    std::shared_ptr<Throw> m_Throw;
    glm::vec2 m_ThrowPosition = {-655, 210};

    // bomb
    std::shared_ptr<Bomb> m_Bomb;
    glm::vec2 m_BombPosition = {-655, 70};

    std::shared_ptr<Util::GameObject> m_Tools = std::make_shared<Util::GameObject>();
};

#endif // FUCK_PTSD_TOOLS_H