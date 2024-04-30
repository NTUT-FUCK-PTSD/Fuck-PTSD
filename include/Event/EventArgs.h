#ifndef EVENT_ARGS_H
#define EVENT_ARGS_H

#include <glm/glm.hpp>

#include "Event/EventType.h"

class EventArgs {
public:
    explicit EventArgs(const EventType type)
        : type(type) {}

    virtual ~EventArgs() {}

    EventType GetType() const { return type; }

private:
    EventType type;
};

class PlayerMoveEventArgs : public EventArgs {
public:
    explicit PlayerMoveEventArgs(const glm::vec2& gamePosition)
        : EventArgs(EventType::PlayerMove),
          m_GamePosition(gamePosition) {}

    glm::vec2 GetGamePosition() const { return m_GamePosition; }

private:
    glm::vec2 m_GamePosition;
};

class EnemyMoveEventArgs : public EventArgs {
public:
    explicit EnemyMoveEventArgs(const std::size_t from, const std::size_t to)
        : EventArgs(EventType::EnemyMove),
          m_Form(from),
          m_To(to) {}

    std::size_t GetFrom() const { return m_Form; }
    std::size_t GetTo() const { return m_To; }

private:
    std::size_t m_Form;
    std::size_t m_To;
};

class AttackPlayerEventArgs : public EventArgs {
public:
    explicit AttackPlayerEventArgs(const std::size_t damage)
        : EventArgs(EventType::AttackPlayer),
          m_Damage(damage) {}

    std::size_t GetDamage() const { return m_Damage; }

private:
    std::size_t m_Damage;
};

#endif  // EVENT_ARGS_H
