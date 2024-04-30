#include "Event/Event.h"

eventpp::EventDispatcher<EventType, void(const EventArgs&), EventPolicies>
    Event::Dispatcher;
