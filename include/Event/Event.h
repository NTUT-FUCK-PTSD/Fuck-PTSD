#ifndef EVENT_H
#define EVENT_H

#include <glm/glm.hpp>
#include "eventpp/eventqueue.h"
#include "eventpp/utilities/scopedremover.h"

#include "Event/EventArgs.h"
#include "Event/EventType.h"
#include "Event/Object.h"

struct EventPolicies {
    static EventType getEvent(const Object*, const EventArgs& event) {
        return event.GetType();
    }
};

class Event final {
public:
    Event() = delete;
    ~Event() = default;
    // using EventQueueHandle = eventpp::EventQueue<
    //     EventType,
    //     void(const Object* sender, const EventArgs& e),
    //     EventPolicies>::Handle;

    static eventpp::EventQueue<
        EventType,
        void(const Object* sender, const EventArgs& e),
        EventPolicies>
        EventQueue;

    using Remover = eventpp::ScopedRemover<eventpp::EventQueue<
        EventType,
        void(const Object* sender, const EventArgs& e),
        EventPolicies>>;

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
