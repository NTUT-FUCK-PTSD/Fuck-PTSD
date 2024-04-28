#ifndef MAP_EVENT_H
#define MAP_EVENT_H

#include <glm/glm.hpp>
#include <memory>
#include "eventpp/callbacklist.h"
#include "eventpp/eventdispatcher.h"
#include "eventpp/eventqueue.h"
#include "eventpp/utilities/orderedqueuelist.h"

namespace Dungeon {
class MapEvent final {
public:
    MapEvent() = delete;
    ~MapEvent() = delete;
    static eventpp::CallbackList<void()>                  ResetMap;
    static eventpp::CallbackList<void(const glm::vec2&)>  PlayerMove;
    static eventpp::CallbackList<void(const std::size_t)> AttackPlayer;
    static eventpp::CallbackList<void(const std::size_t, const std::size_t)>
                                         EnemyMove;
    static eventpp::CallbackList<void()> DrawableUpdate;
};
}  // namespace Dungeon
#endif  // MAP_EVENT_H
