#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "Dungeon/SimpleMapData.h"
#include "Dungeon/Tile.h"
#include "Settings/Window.hpp"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"

#include "Util/GameObject.hpp"

namespace Dungeon {
// Abstract class
class Enemy : public Util::GameObject {
public:
    Enemy(const s_Enemy &u_Enemy,
          const std::shared_ptr<SimpleMapData> simpleMapData);
    virtual ~Enemy() = default;

    void SetShadow(const bool &shadow);
    void SetGamePosition(const glm::vec2 &gamePosition);
    void SetBeatDelay(const std::size_t beatDelay) { m_BeatDelay = beatDelay; }
    void SetLord(const bool &lord);
    void SetDamage(const std::size_t damage) { m_Damage = damage; }
    void SetHealth(const std::size_t health) { m_Health = health; }
    void SetCoin(const std::size_t coin) { m_Coin = coin; }
    void SetCanMove(const bool &canMove) { m_CanMove = canMove; }

    void SetFace(bool faceTo) {
        m_Transform.scale.x = faceTo ? DUNGEON_SCALE : -DUNGEON_SCALE;
    }

    [[nodiscard]]
    glm::vec2 GetPlayerPosition() const {
        return m_SimpleMapData->GetPlayerPosition();
    }
    [[nodiscard]]
    bool GetCanMove() const {
        return m_CanMove;
    }
    [[nodiscard]]
    const glm::vec2 &GetGamePosition() const {
        return m_GamePosition;
    }
    [[nodiscard]]
    std::size_t GetBeatDelay() const {
        return m_BeatDelay;
    }
    [[nodiscard]]
    bool GetLord() const {
        return m_Lord;
    }
    [[nodiscard]]
    bool GetShadow() const {
        return m_Shadow;
    }
    [[nodiscard]]
    std::size_t GetDamage() const {
        return m_Damage;
    }
    [[nodiscard]]
    std::size_t GetHealth() const {
        return m_Health;
    }
    [[nodiscard]]
    std::size_t GetCoin() const {
        return m_Coin;
    }
    [[nodiscard]]
    const glm::vec2 &GetWillMovePosition() const {
        return m_WillMovePosition;
    }
    // DidAttack() is used to check if the enemy has attacked the player
    // it only returns true once after the enemy has attacked the player
    [[nodiscard]]
    bool DidAttack();
    [[nodiscard]]
    bool GetVisible() const {
        return m_Visible;
    }

    virtual glm::vec2 FindNextToPlayer(); // Set available WillMovePosition to
                                          // slowly close PlayerPosition
    void TempoMove();
    bool IsVaildMove(const glm::vec2 &position);
    std::size_t GamePostion2MapIndex(const glm::ivec2 &position) const {
        return m_SimpleMapData->GamePosition2MapIndex(position);
    }
    virtual void Struck(const std::size_t damage) {
        m_Health -= damage;
        if (m_Health <= 0) {
            SetVisible(false);
        }
    };

    virtual void Update() {};

    bool GetSeen() const { return m_Seen; }

protected:
    virtual void Move() = 0;

    virtual void AttackPlayer();

    std::shared_ptr<SimpleMapData> m_SimpleMapData;

    std::shared_ptr<SpriteSheet> m_SpriteSheet;
    std::vector<std::size_t> m_NormalFrames;
    std::vector<std::size_t> m_ShadowFrames;
    glm::vec2 m_GamePosition;
    bool m_CanMove = false;
    glm::vec2 m_WillMovePosition;

    bool m_AttackPlayer = false;

private:
    std::size_t m_BeatDelay;
    bool m_Lord;
    bool m_Shadow = false;
    std::size_t m_Damage = 0;
    std::size_t m_Health = 0; // Notice: 1 heart = 2 health(same as damage)
    std::size_t m_Coin = 0;

    bool m_Seen = false;
};
} // namespace Dungeon

#endif // ENEMY_H
