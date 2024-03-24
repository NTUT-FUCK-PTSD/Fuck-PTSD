//
// Created by adven on 2024/3/24.
//

#include "pch_extream.h"

#include "Tools.h"

Tools::Tools() {

    // create tool shovel
    m_Shovel = std::make_shared<Shovel>();
    m_Shovel->setPosition(m_ShovelPosition);

}

std::shared_ptr<Util::GameObject> Tools::getGameObject() {
    m_Tools->AddChild(m_Shovel->getGameElement());

    m_Tools->SetVisible(true);
    return m_Tools;
}
std::vector<std::shared_ptr<Util::GameObject>> Tools::getGameObjects() {
    return m_Shovel->getGameObjects();
}
