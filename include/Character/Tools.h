

#ifndef FUCK_PTSD_TOOLS_H
#define FUCK_PTSD_TOOLS_H

#include "pch_extream.h"

#include "Equipment.h"
#include "Shovel.h"



class Tools final{
public:
    explicit Tools();

    std::shared_ptr<Util::GameObject> getGameObject();

    std::vector<std::shared_ptr<Util::GameObject>> getGameObjects();
private:
    std::shared_ptr<Shovel> m_Shovel;
    glm::vec2 m_ShovelPosition = {-655, 350};

    std::shared_ptr<Util::GameObject> m_Tools = std::make_shared<Util::GameObject>();
};

#endif // FUCK_PTSD_TOOLS_H