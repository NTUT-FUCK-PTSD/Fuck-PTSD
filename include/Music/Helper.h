#ifndef HELPER_H
#define HELPER_H

#include <array>
#include <cstddef>
#include <vector>

namespace Music {
class Helper {
public:
    struct SBSResult {
        bool        onTempoIdx;
        std::size_t BeforeTempoIdx;
        std::size_t AfterTempoIDx;
    };
    static SBSResult BinarySearch(
        const std::vector<std::size_t>& vec,
        std::size_t                     target
    ) {
        std::size_t left = 0;
        std::size_t right = vec.size() - 1;
        std::size_t mid = 0;

        while (left <= right) {
            mid = left + (right - left) / 2;

            if (vec[mid] == target) {
                return {true, mid, mid};
            } else if (vec[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return {false, right, left};
    }
};

}  // namespace Music

#endif  // HELPER_H
