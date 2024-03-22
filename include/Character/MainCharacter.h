//
// Created b adven on 2024/3/4.
//

#ifndef FUCK_PTSD_MAINCHARACTER_H
#define FUCK_PTSD_MAINCHARACTER_H

#include "Core/Drawable.hpp"
#include "GameElement.h"
#include "Util/Root.hpp"
#include <iostream>

class MainCharacter {
private:
    std::string m_BodyImagePath = ASSETS_DIR "/entities/player1_armor_body.png";

    std::string m_HeadImagePath = ASSETS_DIR "/entities/player1_heads.png";
    //    std::shared_ptr<GameElement> m_MainCharacter =
    //        std::make_shared<GameElement>();

    std::shared_ptr<GameElement> m_Body = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Head = std::make_shared<GameElement>();

    glm::vec2 InitPosition = {0, 0};

    float ZIndex = 0.5;

    uint16_t m_start_move_animation_frame = 0;

public:
    enum Direction { UP = 0, RIGHT, DOWN, LEFT, NONE };

    explicit MainCharacter();

    [[nodiscard]] const std::vector<std::shared_ptr<Util::GameObject>>
    GetGameElement() const;

    /* ---- Setter and Getter ----- */
public:
    [[nodiscard]] uint16_t GetStartMoveFrame() const {
        return m_start_move_animation_frame;
    }

    [[nodiscard]] glm::vec2 GetPosition() const {
        return m_Head->GetPosition();
    };

    [[nodiscard]] glm::vec2 GetGamePosition();

    void SetPosition(const glm::vec2 &position);

    void SetBodyImagePath(const std::string &Path) { m_BodyImagePath = Path; };

    void SetHeadImagePath(const std::string &Path) { m_HeadImagePath = Path; }

    void SetFaceTo(Direction direction);

    void SetZIndex(float index) {
        ZIndex = index;
        m_Body->SetZIndex(index);
        m_Head->SetZIndex(index + float(0.25));
    }

    void Update() { SetZIndex(GetGamePosition().y + float(0.5)); }
};

#endif // FUCK_PTSD_MAINCHARACTER_H
