#ifndef TEMPO_H
#define TEMPO_H

#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Util/Logger.hpp"

#include "Helper.h"

namespace Music {
class Tempo {
public:
    static void ReadTempoFile(const std::string& path);

    [[nodiscard]]
    static bool IsTempoInRange(
        const std::size_t triggerRange,
        const float       time
    );

    [[nodiscard]]
    static std::size_t GetCurrentBeatIdx(
        const float       time,
        const std::size_t offset
    );

    // value
    static std::size_t m_BeatListLen;
    // static std::size_t m_CurrentBeatIdx;

private:
    static void LopReset();

    static std::vector<std::size_t> m_BeatList;
    static std::vector<bool>        m_IsBeatClick;
    static std::size_t              m_CurrentBeatLopTimes;
    static std::size_t              m_CurrentBeatIdx;
};
}  // namespace Music

#endif  // TEMPO_H
