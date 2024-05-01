#include "Event/Event.h"

eventpp::EventDispatcher<
    EventType,
    void(const Object* sender, const EventArgs& e),
    EventPolicies>
     Event::Dispatcher;
bool Event::m_AttackPlayer = false;
