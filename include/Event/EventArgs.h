#ifndef EVENT_ARGS_H
#define EVENT_ARGS_H

#include <glm/glm.hpp>

#include "Event/EventType.h"

class EventArgs {
public:
    explicit EventArgs(const EventType type)
        : type(type) {}

    virtual ~EventArgs() = default;

    EventType GetType() const { return type; }

private:
    EventType type;
};

class EnemyMoveEventArgs : public EventArgs {
public:
    explicit EnemyMoveEventArgs(const std::size_t mapIndex)
        : EventArgs(EventType::EnemyMove),
          m_MapIndex(mapIndex) {}

    std::size_t GetMapIndex() const { return m_MapIndex; }

private:
    std::size_t m_MapIndex;
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
