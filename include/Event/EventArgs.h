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
    // (type, getter, setter)
    (std::size_t, GetMapIndex)
);

EVENTPP_MAKE_EVENT(
    AttackPlayerEventArgs,
    EventArgs,
    EventType::AttackPlayer,
    (std::size_t, GetDamage)
);

EVENTPP_MAKE_EVENT(
    EnemyRemoveEventArgs,
    EventArgs,
    EventType::EnemyRemove,
    (std::size_t, GetMapIndex)
);

EVENTPP_MAKE_EVENT(
    WallRemoveEventArgs,
    EventArgs,
    EventType::WallRemove,
    (std::size_t, GetMapIndex)
);

EVENTPP_MAKE_EVENT(
    FloorUpdateEventArgs,
    EventArgs,
    EventType::FloorUpdate,
    (std::size_t, GetTempoIndex),
    (bool, GetColored)
);

#endif  // EVENT_ARGS_H
