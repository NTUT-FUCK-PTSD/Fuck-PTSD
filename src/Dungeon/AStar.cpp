#include "Dungeon/AStar.h"

#include <algorithm>
#include <queue>
#include <unordered_set>

namespace Dungeon {
std::vector<glm::ivec2>
AStar::FindPath(const glm::ivec2 &start, const glm::ivec2 &end,
                const std::shared_ptr<SimpleMapData> &mapData) {
    std::vector<glm::ivec2> path;
    std::vector<glm::ivec2> directions = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
    };

    std::priority_queue<std::pair<float, glm::ivec2>,
                        std::vector<std::pair<float, glm::ivec2>>, NodeCompare>
        frontier;
    frontier.push({0, start});

    std::vector<glm::ivec2> cameFrom(mapData->GetSize().x *
                                     mapData->GetSize().y);

    std::vector<float> costSoFar(mapData->GetSize().x * mapData->GetSize().y,
                                 std::numeric_limits<float>::max());

    std::pair<float, glm::ivec2> lastminPath = {
        std::numeric_limits<float>::max(), start};
    costSoFar[mapData->GamePosition2MapIndex(start)] = 0;

    while (!frontier.empty()) {
        std::pair<float, glm::ivec2> current = frontier.top();
        frontier.pop();
        if (Heuristic(current.second, end) <
            Heuristic(lastminPath.second, end)) {
            lastminPath = current;
        }

        if (current.second == end) {
            path = CalculatePath(cameFrom, start, end, mapData);
            break;
        }

        for (const auto &direction : directions) {
            glm::ivec2 next = current.second + direction;
            // if the position is not walkable
            if (mapData->IsPositionWalkable(next) == false) {
                continue;
            }

            float newCost = current.first + Heuristic(current.second, next);
            size_t mapIndex = mapData->GamePosition2MapIndex(next);
            if (newCost < costSoFar[mapIndex]) {
                costSoFar[mapIndex] = newCost;
                float priority = newCost + Heuristic(next, end);
                frontier.push({priority, next});
                cameFrom[mapIndex] = current.second;
            }
        }
    }

    if (path.empty()) {
        if (mapData->IsPositionWalkable(lastminPath.second) == false) {
            return path;
        }
        path = CalculatePath(cameFrom, start, lastminPath.second, mapData);
    }
    return path;
}

float AStar::Heuristic(const glm::ivec2 &start, const glm::ivec2 &end) {
    auto difference = abs(glm::vec2(start) - glm::vec2(end));
    return difference.x + difference.y;
}

std::vector<glm::ivec2>
AStar::CalculatePath(const std::vector<glm::ivec2> &cameFrom,
                     const glm::ivec2 &start, const glm::ivec2 &end,
                     const std::shared_ptr<SimpleMapData> &mapData) {
    std::vector<glm::ivec2> path;
    glm::ivec2 current = end;
    while (current != start) {
        path.push_back(current);
        current = cameFrom[mapData->GamePosition2MapIndex(current)];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}
} // namespace Dungeon
