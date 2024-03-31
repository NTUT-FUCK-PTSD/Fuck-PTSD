//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_BOMB_H
#define FUCK_PTSD_BOMB_H

#include "Util/Color.hpp"
#include "Util/Text.hpp"
#include "pch_extream.h"

#include "IEquipment.h"
#include "ToolBoxs.h"

class Bomb final : public IEquipment {
public:
    explicit Bomb();

    [[nodiscard]] std::shared_ptr<GameElement> getGameElement() override;

    void setPosition(const glm::vec2 position) override;

    std::vector<std::shared_ptr<Util::GameObject>> getGameObjects() override;

    std::shared_ptr<GameElement> GetGameObject() const override;

private:
    std::size_t m_ZIndex = 50;
    glm::vec2 m_Scale = {3, 3};
    glm::vec2 m_Position = {0, 0};

    Util::Color m_FontColor = Util::Color(255, 255, 255);
    glm::vec2 m_FontScale = {5, 5};
    std::size_t m_FontSize = 6;
    std::string m_Content = "DOWN";
    std::string m_TextStylePath =
        ASSETS_DIR "/font/necrosans-6/necrosans-6.otf";

    std::string m_ImagePathWindow = ASSETS_DIR "/gui/hud_slot_bomb.png";
    std::string m_ImagePathItem = ASSETS_DIR "/items/bomb.png";

    std::shared_ptr<GameElement> m_Window = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Item = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Text = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_LowerText = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Bomb = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_BOMB_H
