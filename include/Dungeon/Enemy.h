#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "Dungeon/Elements.h"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"

#include "Util/GameObject.hpp"

namespace Dungeon {
// Abstract class
class Enemy : public Util::GameObject {
public:
    Enemy(const s_Enemy &u_Enemy);

    void SetShadow(bool shadow);
    void SetPosition(const glm::vec2 &position);
    void SetBeatDelay(size_t beatDelay) { m_BeatDelay = beatDelay; }
    void SetLord(bool lord);
    void SetDamage(size_t damage) { m_Damage = damage; }
    void SetHealth(size_t health) { m_Health = health; }
    void SetCoin(size_t coin) { m_Coin = coin; }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Position; }
    [[nodiscard]] size_t GetBeatDelay() const { return m_BeatDelay; }
    [[nodiscard]] bool GetLord() const { return m_Lord; }
    [[nodiscard]] bool GetShadow() const { return m_Shadow; }
    [[nodiscard]] size_t GetDamage() const { return m_Damage; }
    [[nodiscard]] size_t GetHealth() const { return m_Health; }
    [[nodiscard]] size_t GetCoin() const { return m_Coin; }

    void TempoMove();
    virtual void Move() = 0;

protected:
    std::shared_ptr<SpriteSheet> m_SpriteSheet;
    std::vector<std::size_t> m_NormalFrames;
    std::vector<std::size_t> m_ShadowFrames;

private:
    glm::vec2 m_Position;
    size_t m_BeatDelay;
    bool m_Lord;
    bool m_Shadow = false;
    size_t m_Damage = 0;
    size_t m_Health = 0; // Notice: 1 heart = 2 health(same as damage)
    size_t m_Coin = 0;
};
} // namespace Dungeon

#endif // ENEMY_H
