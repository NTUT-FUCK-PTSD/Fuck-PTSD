#ifndef EVENT_ARGS_H
#define EVENT_ARGS_H

#include <glm/glm.hpp>
#include "eventpp/utilities/eventmaker.h"

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

EVENTPP_MAKE_EVENT(
    EnemyMoveEventArgs,
    EventArgs,
    EventType::EnemyMove,
    (std::size_t, GetMapIndex)
);

EVENTPP_MAKE_EVENT(
    AttackPlayerEventArgs,
    EventArgs,
    EventType::AttackPlayer,
    (std::size_t, GetDamage)
);

#endif  // EVENT_ARGS_H
