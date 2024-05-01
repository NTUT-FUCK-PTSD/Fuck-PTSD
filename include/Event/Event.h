#ifndef EVENT_H
#define EVENT_H

#include <glm/glm.hpp>
#include "eventpp/eventdispatcher.h"

#include "Event/EventArgs.h"
#include "Event/Object.h"

struct EventPolicies {
    template <typename T>
    static EventType getEvent(const T& event) {
        return event.getType();
    }
};

class Event final {
public:
    Event() = delete;
    ~Event() = default;
    using DispatcherHandle = eventpp::EventDispatcher<
        EventType,
        void(const Object* sender, const EventArgs& e),
        EventPolicies>::Handle;

    static eventpp::EventDispatcher<
        EventType,
        void(const Object* sender, const EventArgs& e),
        EventPolicies>
        Dispatcher;

    static void SetAttackPlayer(bool attackPlayer) {
        m_AttackPlayer = attackPlayer;
    }
    [[nodiscard]]
    static bool GetAttackPlayer() {
        return m_AttackPlayer;
    }

private:
    static bool m_AttackPlayer;
};

#endif  // EVENT_H
