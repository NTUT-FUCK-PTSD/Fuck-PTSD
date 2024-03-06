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

    uint16_t ZIndex = 50;

    uint16_t m_start_move_animation_frame = 0;

public:
    enum Direction { UP = 0, DOWN, RIGHT, LEFT, NONE };

    explicit MainCharacter();

    [[nodiscard]] const std::vector<std::shared_ptr<Util::GameObject>>
    Render() const;

    void player_back(const int current_frames);

    void move_player(const glm::vec2 distance);

    void player_move_animation(const int current_framesm, Direction direction);

    /* ---- Setter and Getter ----- */
public:
    [[nodiscard]] uint16_t GetStartMoveFrame() const {
        return m_start_move_animation_frame;
    }

    void SetBodyImagePath(const std::string &Path) { m_BodyImagePath = Path; };

    void SetHeadImagePath(const std::string &Path) { m_HeadImagePath = Path; }
};

#endif // FUCK_PTSD_MAINCHARACTER_H
