#ifndef EVENT_H
#define EVENT_H

#include <glm/glm.hpp>
#include "eventpp/eventdispatcher.h"

#include "Event/EventArgs.h"

struct EventPolicies {
    template <typename T>
    static EventType getEvent(const T& event) {
        return event.getType();
    }
};

class Event final {
public:
    Event() = delete;
    ~Event() = delete;
    using DispatcherHandle = eventpp::EventDispatcher<
        EventType,
        void(const EventArgs&),
        EventPolicies>::Handle;

    static eventpp::
        EventDispatcher<EventType, void(const EventArgs&), EventPolicies>
            Dispatcher;
};

#endif  // EVENT_H
