#ifndef MAP_EVENT_H
#define MAP_EVENT_H

#include <glm/glm.hpp>
#include "eventpp/eventdispatcher.h"

enum class EventType {
    ResetMap,
    DrawableUpdate,
    AttackPlayer,
    PlayerMove,
    EnemyMove,
};

struct EventArgs {
    EventType   type;
    std::size_t damage;
    std::size_t from;
    std::size_t to;
    glm::vec2   gamePosition;
};

struct EventPolicies {
    static EventType getEvent(const EventArgs& e) { return e.type; }
};

namespace Dungeon {
class MapEvent final {
public:
    MapEvent() = delete;
    ~MapEvent() = delete;
    using DispatcherHandle = eventpp::EventDispatcher<
        EventType,
        void(const EventArgs&),
        EventPolicies>::Handle;
    static eventpp::
        EventDispatcher<EventType, void(const EventArgs&), EventPolicies>
            Dispatcher;
};
}  // namespace Dungeon
#endif  // MAP_EVENT_H
