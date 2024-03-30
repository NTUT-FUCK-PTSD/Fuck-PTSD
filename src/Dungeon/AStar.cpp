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
    costSoFar[mapData->GamePostion2MapIndex(start)] = 0;

    while (!frontier.empty()) {
        auto current = frontier.top().second;
        frontier.pop();

        if (current == end) {
            path = CalculatePath(cameFrom, start, end, mapData);
            break;
        }

        for (const auto &direction : directions) {
            glm::ivec2 next = current + direction;

            if (mapData->IsPositionValid(next) == false) {
                continue;
            }

            if (mapData->IsTilesEmpty(mapData->GamePostion2MapIndex(next))) {
                continue;
            }

            if (mapData->GetTileBack(mapData->GamePostion2MapIndex(next))
                    ->IsWall()) {
                continue;
            }

            if (mapData->GetTileBack(mapData->GamePostion2MapIndex(next))
                    ->IsDoor()) {
                continue;
            }

            float newCost = costSoFar[mapData->GamePostion2MapIndex(current)] +
                            Heuristic(current, next);

            if (newCost < costSoFar[mapData->GamePostion2MapIndex(next)]) {
                costSoFar[mapData->GamePostion2MapIndex(next)] = newCost;
                float priority = newCost + Heuristic(next, end);
                frontier.push({priority, next});
                cameFrom[mapData->GamePostion2MapIndex(next)] = current;
            }
        }
    }

    return path;
}

float AStar::Heuristic(const glm::ivec2 &start, const glm::ivec2 &end) {
    return glm::distance(glm::vec2(start), glm::vec2(end));
}

std::vector<glm::ivec2>
AStar::CalculatePath(const std::vector<glm::ivec2> &cameFrom,
                     const glm::ivec2 &start, const glm::ivec2 &end,
                     const std::shared_ptr<SimpleMapData> &mapData) {
    std::vector<glm::ivec2> path;
    glm::ivec2 current = end;
    while (current != start) {
        path.push_back(current);
        current = cameFrom[mapData->GamePostion2MapIndex(current)];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}
} // namespace Dungeon
