//
// Created b adven on 2024/3/4.
//

#ifndef FUCK_PTSD_MAINCHARACTER_H
#define FUCK_PTSD_MAINCHARACTER_H

#include "Dungeon/Elements.h"
#include "GameElement.h"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"
#include "Util/Time.hpp"

class MainCharacter {
private:
    std::string m_HeadImagePath;
    std::string m_BodyImagePath;

    glm::vec2 HeadSize;
    glm::vec2 BodySize;
    std::shared_ptr<SpriteSheet> HeadImage;
    std::shared_ptr<SpriteSheet> BodyImage;

    std::shared_ptr<GameElement> m_Body = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_Head = std::make_shared<GameElement>();

    const glm::vec2 InitPosition = {0, 0};
    glm::vec2 m_Position = {0, 0};
    glm::vec2 m_GamePosition = {0, 0};

    float m_ZIndex = 0.5;

    const std::vector<glm::vec2> m_MoveAnimation = {
        {0, Dungeon::DUNGEON_TILE_WIDTH},
        {Dungeon::DUNGEON_TILE_WIDTH / 2, Dungeon::DUNGEON_TILE_WIDTH},
        {-Dungeon::DUNGEON_TILE_WIDTH / 4, Dungeon::DUNGEON_TILE_WIDTH},
        {-Dungeon::DUNGEON_TILE_WIDTH / 2, Dungeon::DUNGEON_TILE_WIDTH}};

    bool m_IsAnimating = false;
    unsigned long m_AnimationStartMs;
    unsigned long m_AnimationEndMs;
    unsigned long m_AnimationDuringTimeMs;
    glm::vec2 m_AnimationDestination;
    uint16_t m_AnimationDirection;

    void SetPosition(const glm::vec2 &position);

public:
    enum Direction { UP = 0, RIGHT, DOWN, LEFT, NONE };

    MainCharacter(const std::string &headImagePath,
                  const std::string &bodyImagePath);

    [[nodiscard]] const std::vector<std::shared_ptr<Util::GameObject>>
    GetGameElement() const;

    /* ---- Setter and Getter ----- */
public:
    [[nodiscard]] glm::vec2 GetGamePosition();

    void SetGamePosition(const glm::vec2 &position);

    void SetBodyImagePath(const std::string &Path) { m_BodyImagePath = Path; };

    void SetHeadImagePath(const std::string &Path) { m_HeadImagePath = Path; }

    void SetFaceTo(Direction direction);

    void SetZIndex(float index);

    void MoveByTime(const unsigned long &duringTimeMs,
                    const glm::vec2 &destGamePosition, Direction direction);

    void Update();
};

#endif // FUCK_PTSD_MAINCHARACTER_H
