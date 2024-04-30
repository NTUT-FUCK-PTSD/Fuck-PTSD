#include "Dungeon/MapEvent.h"

eventpp::EventDispatcher<EventType, void(const Event&), EventPolicies>
    Dungeon::MapEvent::Dispatcher;
