#ifndef DIRECTION_H
#define DIRECTION_H

#include <glm/glm.hpp>

namespace Dungeon {
constexpr static const glm::vec2 TOP_LEFT = glm::vec2(-1.0f, -1.0f);
constexpr static const glm::vec2 TOP = glm::vec2(0.0f, -1.0f);
constexpr static const glm::vec2 TOP_RIGHT = glm::vec2(1.0f, -1.0f);
constexpr static const glm::vec2 LEFT = glm::vec2(-1.0f, 0.0f);
constexpr static const glm::vec2 RIGHT = glm::vec2(1.0f, 0.0f);
constexpr static const glm::vec2 BOTTOM_LEFT = glm::vec2(-1.0f, 1.0f);
constexpr static const glm::vec2 BOTTOM = glm::vec2(0.0f, 1.0f);
constexpr static const glm::vec2 BOTTOM_RIGHT = glm::vec2(1.0f, 1.0f);
}  // namespace Dungeon

#endif  // DIRECTION_H
