//
// Created b adven on 2024/3/4.
//

#ifndef FUCK_PTSD_PLAYER_H
#define FUCK_PTSD_PLAYER_H

#include "Animation.h"
#include "GameElement.h"
#include "Items/Coin.h"
#include "Items/Diamond.h"
#include "Items/Heart.h"
#include "Items/Tools.h"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"

class Player : public Animation {
public:
    enum Direction { UP = 0, RIGHT, DOWN, LEFT, NONE };

    explicit Player();

    virtual ~Player() = default;

    // some getter
    std::shared_ptr<GameElement> GetGameElement();
    [[nodiscard]] glm::vec2 GetGamePosition();
    std::shared_ptr<GameElement> GetWindowElement();

    // set player's settings
    void SetGamePosition(const glm::vec2 &position);
    void SetBodyImagePath(const std::string &Path) { m_BodyImagePath = Path; };
    void SetHeadImagePath(const std::string &Path) { m_HeadImagePath = Path; }
    void SetFaceTo(Direction direction);
    void SetZIndex(float index);

    // set player outside
    void SetHeadImage(const std::string &path);
    void SetHeadImage(std::shared_ptr<SpriteSheet> image);
    void SetBodyImage(const std::string &path);
    void SetBodyImage(std::shared_ptr<SpriteSheet> image);

    // set player's item
    void gainCoin(std::size_t number);
    void lostCoin(std::size_t number);
    void gainDiamond(std::size_t number);
    void lostDiamond(std::size_t number);

    // DOTO: set player's heart
    void lostHP(std::size_t value);
    void gainHeart(std::size_t value);
    void getHP(std::size_t value);

    // set player's tool
    void useDefaultSettingsTool();

    // update
    void Update();

    // some unused functional
    void UpdateCoin(const unsigned long duringTimeMs,
                    const glm::vec2 &destination, const uint16_t direction);

    // tool's handle
    // about Shovel
    bool IsShovelExist();
    ShovelEnum::Type GetShovelType();

    // about Weapon
    bool IsWeaponExist();
    WeaponEnum::Type GetWeaponType();

    virtual void MoveByTime(const unsigned long duringTimeMs,
                            const glm::vec2 &destination,
                            const uint16_t direction) override;

private:
    ShovelEnum::Type m_ShovelType = ShovelEnum::Type::Normal;
    WeaponEnum::Type m_WeaponType = WeaponEnum::Type::DAGGER;

    std::string m_HeadImagePath;
    std::string m_BodyImagePath;

    // character settings
    glm::vec2 HeadSize;
    glm::vec2 BodySize;
    std::shared_ptr<SpriteSheet> HeadImage;
    std::shared_ptr<SpriteSheet> BodyImage;

    // game object
    std::shared_ptr<GameElement> m_Body;
    std::shared_ptr<GameElement> m_Head;
    std::shared_ptr<GameElement> m_Player;

    std::unique_ptr<Coin> m_Coin;
    std::unique_ptr<Heart> m_Heart;
    std::unique_ptr<Tools> m_Tools;
    std::unique_ptr<Diamond> m_Diamond;
    std::shared_ptr<GameElement> m_Window;

    glm::vec2 m_Position = {0, 0};
    glm::vec2 m_GamePosition = {0, 0};

    float m_ZIndex = 0.5;

    void SetPosition(const glm::vec2 &position);
};

#endif // FUCK_PTSD_PLAYER_H
