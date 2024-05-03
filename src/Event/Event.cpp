#include "Event/Event.h"

eventpp::EventQueue<
    EventType,
    void(const Object* sender, const EventArgs& e),
    EventPolicies>
     Event::EventQueue;
bool Event::m_AttackPlayer = false;
