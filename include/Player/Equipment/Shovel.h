//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_SHOVEL_H
#define FUCK_PTSD_SHOVEL_H

#include "pch_extream.h"

#include "IEquipment.h"
#include "ToolBoxs.h"

class Shovel final : public IEquipment {
public:
    explicit Shovel();

    [[nodiscard]] std::shared_ptr<GameElement> getGameElement() override;

    void setPosition(const glm::vec2 position) override;

    std::vector<std::shared_ptr<Util::GameObject>> getGameObjects() override;

    std::shared_ptr<GameElement> GetGameObject() const override;
private:
    std::size_t m_ZIndex = 50;
    glm::vec2 m_Scale = {3,3 };
    glm::vec2 m_Position = {0, 0};

//    ASSETS_DIR "/gui/diamond.png"

    std::string m_ImagePathWindow = ASSETS_DIR "/gui/hud_slot_1.png";
    std::string m_ImagePathItem = ASSETS_DIR "/items/shovel_basic.png";

    std::shared_ptr<GameElement> m_Window = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Item = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Shovel = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_SHOVEL_H
