//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_THROW_H
#define FUCK_PTSD_THROW_H

#include "Util/Text.hpp"
#include "pch_extream.h"

#include "IEquipment.h"
#include "ToolBoxs.h"

class Throw final : public IEquipment {
public:
    explicit Throw();

    void setPosition(const glm::vec2 position) override;

    std::shared_ptr<GameElement> GetGameObject() const override;
    Direction GetDirection() override { return IEquipment::Direction::COL; };

private:
    std::size_t m_ZIndex = 99;
    glm::vec2 m_Scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    glm::vec2 m_Position = {0, 0};

    Util::Color m_FontColor = Util::Color(255, 255, 255);
    glm::vec2 m_FontScale = {5, 5};
    std::size_t m_FontSize = 6;
    std::string m_Content = "UP+";
    std::string m_TextStylePath =
        ASSETS_DIR "/font/necrosans-6/necrosans-6.otf";

    //    ASSETS_DIR "/gui/diamond.png"

    std::string m_ImagePathWindow = ASSETS_DIR "/gui/hud_slot_throw.png";
    std::string m_ImagePathItem = ASSETS_DIR "/items/weapon_dagger.png";

    std::shared_ptr<GameElement> m_Window = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Item = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Text = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_LowerText = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Throw = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_THROW_H
