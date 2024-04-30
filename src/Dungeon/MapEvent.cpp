#include "Dungeon/MapEvent.h"

eventpp::EventDispatcher<EventType, void(const EventArgs&), EventPolicies>
    Dungeon::MapEvent::Dispatcher;
