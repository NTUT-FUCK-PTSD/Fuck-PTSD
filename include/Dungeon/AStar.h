#ifndef AStar_H
#define AStar_H

#include "Dungeon/SimpleMapData.h"

namespace Dungeon {
class AStar final {
public:
    static std::vector<glm::ivec2>
    FindPath(const glm::ivec2 &start, const glm::ivec2 &end,
             const std::shared_ptr<SimpleMapData> &mapData);

private:
    struct NodeCompare {
        bool operator()(const std::pair<float, glm::ivec2> &lhs,
                        const std::pair<float, glm::ivec2> &rhs) {
            return lhs.first > rhs.first;
        }
    };
    static std::vector<glm::ivec2>
    CalculatePath(const std::vector<glm::ivec2> &cameFrom,
                  const glm::ivec2 &start, const glm::ivec2 &end,
                  const std::shared_ptr<SimpleMapData> &mapData);
};
} // namespace Dungeon

#endif // AStar_H
