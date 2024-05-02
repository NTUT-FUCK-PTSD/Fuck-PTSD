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
    // constructor
    explicit Tempo();

    // destructor
    virtual ~Tempo() = default;

    static void ReadTempoFile(const std::string& path);

    static void Pause(bool state);

    [[nodiscard]]
    static bool IsSwitch();

    [[nodiscard]]
    static bool IsTempoInRange(
        const std::size_t triggerRange,
        const std::size_t time,
        const std::size_t MusicLoopCounter
    );

    [[nodiscard]]
    static std::size_t GetBeatIdx();

    [[nodiscard]]
    static std::size_t GetBeatTime();

    [[nodiscard]]
    static std::size_t GetBeatValue(std::size_t idx);

    [[nodiscard]]
    static std::size_t GetBeatListLen();

    static void Update(
        const std::size_t musicPlaytTime,
        const std::size_t triggerOffset,
        const std::size_t MusicLoopCounter
    );

    static std::size_t m_BeatListLen;

private:
    static void LopReset();

    static bool                     m_IsPause;
    static bool                     m_IsBeatSwitch;
    static std::size_t              m_CurrentBeatIdx;
    static std::vector<std::size_t> m_BeatList;
    static std::vector<bool>        m_IsBeatClick;
    static std::size_t              m_CurrentBeatLopTimes;
};
}  // namespace Music

#endif  // TEMPO_H
