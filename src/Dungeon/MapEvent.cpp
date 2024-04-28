#include "Dungeon/MapEvent.h"
#include "eventpp/callbacklist.h"

namespace Dungeon {
eventpp::CallbackList<void()>                  MapEvent::ResetMap;
eventpp::CallbackList<void(const glm::vec2&)>  MapEvent::PlayerMove;
eventpp::CallbackList<void(const std::size_t)> MapEvent::AttackPlayer;
eventpp::CallbackList<void(const std::size_t, const std::size_t)>
                              MapEvent::EnemyMove;
eventpp::CallbackList<void()> MapEvent::DrawableUpdate;
}  // namespace Dungeon
