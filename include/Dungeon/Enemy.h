#ifndef ENEMY_H
#define ENEMY_H

#include "Event/Object.h"
#include "Util/GameObject.hpp"

#include <memory>
#include "Dungeon/SimpleMapData.h"
#include "Event/Event.h"
#include "Settings/Animation.h"
#include "Settings/SpriteSheet.hpp"
#include "Settings/Window.hpp"
#include "UGameElement.h"

namespace Dungeon {
// Abstract class
class Enemy : public Object, public Util::GameObject {
public:
    Enemy(
        const s_Enemy&                       u_Enemy,
        const std::shared_ptr<SimpleMapData> simpleMapData
    );
    virtual ~Enemy();

    void SetShadow(const bool shadow);
    void SetGamePosition(const glm::vec2& gamePosition);
    void SetBeatDelay(const std::size_t beatDelay) { m_BeatDelay = beatDelay; }
    void SetLord(const bool lord);
    void SetDamage(const std::size_t damage) { m_Damage = damage; }
    void InitHealth(const std::size_t health);
    void SetCoin(const std::size_t coin) { m_Coin = coin; }
    void CanMove();

    void SetFace(bool faceTo) {
        m_Transform.scale.x = faceTo ? DUNGEON_SCALE : -DUNGEON_SCALE;
    }

    glm::vec2 GetPlayerPosition() const {
        return m_SimpleMapData->GetPlayerPosition();
    }
    const glm::vec2& GetGamePosition() const { return m_GamePosition; }
    std::size_t      GetID() const { return m_ID; }
    std::size_t      GetBeatDelay() const { return m_BeatDelay; }
    bool             GetLord() const { return m_Lord; }
    bool             GetShadow() const { return m_Shadow; }
    std::size_t      GetDamage() const { return m_Damage; }
    std::size_t      GetHealth() const { return m_Health; }
    std::size_t      GetCoin() const { return m_Coin; }
    const glm::vec2& GetWillMovePosition() const { return m_WillMovePosition; }
    bool             GetVisible() const { return m_Visible; }

    virtual glm::vec2 FindNextToPlayer();  // Set available WillMovePosition to
                                           // slowly close PlayerPosition
    void        TempoMove();
    bool        IsVaildMove(const glm::vec2& position);
    std::size_t GamePostion2MapIndex(const glm::ivec2& position) const {
        return m_SimpleMapData->GamePosition2MapIndex(position);
    }
    virtual void Struck(const std::size_t damage);
    virtual void Update();

    bool GetSeen() const { return m_Seen; }

    glm::vec2 GetPlayerPosition() {
        return m_SimpleMapData->GetPlayerPosition();
    }
    float Heuristic(const glm::vec2& start, const glm::vec2& end) {
        return m_SimpleMapData->Heuristic(start, end);
    }
    void SetCameraUpdate(bool cameraUpdate);

protected:
    virtual void Move() = 0;

    virtual void AttackPlayer();

    virtual void UpdateAnimationType(const glm::vec2& direction);

    void InitHealthBarImage(const glm::vec2& pixelPos);

    virtual void UpdateHeart(const glm::vec2& pixelPos);

    std::shared_ptr<Util::Image>    m_FullHeart;
    std::shared_ptr<Util::Image>    m_EmptyHeart;
    std::vector<Util::GameElement*> m_HeartList;

    std::shared_ptr<SimpleMapData> m_SimpleMapData;

    std::shared_ptr<SpriteSheet> m_SpriteSheet;
    std::vector<std::size_t>     m_NormalFrames;
    std::vector<std::size_t>     m_ShadowFrames;
    glm::vec2                    m_WillMovePosition;

    std::unique_ptr<Animation> m_Animation;

    std::size_t m_AnimationType = 0;

private:
    glm::vec2 m_GamePosition;

    std::size_t m_ID;
    std::size_t m_BeatDelay;
    bool        m_Lord;
    bool        m_IsBeAttacked = false;
    bool        m_Shadow = false;
    std::size_t m_Damage = 0;
    std::size_t m_Health = 0;  // Notice: 1 heart = 2 health(same as damage)
    std::size_t m_Coin = 0;

    bool m_Seen = false;

    Event::DispatcherHandle m_DrawableUpdate;
};
}  // namespace Dungeon

#endif  // ENEMY_H
