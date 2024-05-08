#include "Music/Tempo.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "Music/Player.h"

// TODO: OUT of Range

void Music::Tempo::ReadTempoFile(const std::string& path) {
    // read tempo file

    std::ifstream txtTempoFile(path);

    if (!txtTempoFile.is_open()) {
        LOG_ERROR("fuck it can not open this file");
        return;
    }

    std::string line;
    std::getline(txtTempoFile, line);

    // m_tempoList = txtToVector(line, ',');

    // translate string that tempo file to int vector
    std::stringstream        ss(line);
    std::string              item;
    std::size_t              transform = 0;
    std::vector<std::size_t> elems;
    while (std::getline(ss, item, ',')) {
        transform = std::stoi(item);
        elems.push_back(std::move(transform));
    }

    LOG_ERROR("hello");

    if (elems.empty()) {
        // throw std::exception("tempo list is empty");
        return;
    }

    // save to class member
    m_BeatListLen = elems.size();
    m_IsBeatClick = std::vector<bool>(m_BeatListLen, false);
    m_BeatList = std::move(elems);

    // 关闭文件流
    txtTempoFile.close();
}

void Music::Tempo::Pause(bool state) {
    m_IsPause = state;
}

bool Music::Tempo::IsTempoInRange(
    const std::size_t triggerRange,
    const std::size_t time,
    const std::size_t MusicLoopCounter
) {
    // TODO: //
    if (m_CurrentBeatLopTimes != MusicLoopCounter) {
        m_CurrentBeatLopTimes = MusicLoopCounter;
        LopReset();
    }

    auto time_int = static_cast<std::size_t>(time);
    if (time_int > m_BeatList.back()) {
        return false;
    }

    auto [isOnTempo, BeforeTempo, AfterTempo] =
        Helper::BinarySearch(m_BeatList, time_int);

    if (isOnTempo) {
        return true;
    }

    if (BeforeTempo < 0 || AfterTempo >= m_BeatListLen - 1) {
        return false;
    }

    const auto BeforeTempoTime = m_BeatList.at(BeforeTempo);
    const auto AfterTempoTime = m_BeatList.at(AfterTempo);
    if (BeforeTempoTime + triggerRange <= time
        || AfterTempoTime - triggerRange >= time
        || m_IsBeatClick.at(BeforeTempo) || m_IsBeatClick.at(AfterTempo)) {
        return false;
    }

    const auto& v = m_BeatList;
    if (BeforeTempoTime + triggerRange >= time) {
        auto it = std::find(v.begin(), v.end(), BeforeTempoTime);

        auto dis = std::distance(v.begin(), it);
        m_IsBeatClick.at(dis) = true;
        return true;
    }

    if (AfterTempoTime - triggerRange <= time) {
        auto it = std::find(v.begin(), v.end(), AfterTempoTime);

        auto dis = std::distance(v.begin(), it);
        m_IsBeatClick.at(dis) = true;
        return true;
    }
    return false;
}

bool Music::Tempo::IsSwitch() {
    if (m_IsBeatSwitch) {
        m_IsBeatSwitch = false;
        return true;
    }
    return false;
}

std::size_t Music::Tempo::GetBeatIdx() {
    return m_CurrentBeatIdx;
}

std::size_t Music::Tempo::GetBeatTime() {
    return m_BeatList.at(m_CurrentBeatIdx);
}

void Music::Tempo::LopReset() {
    m_CurrentBeatIdx = 0;
    m_IsBeatClick = std::vector<bool>(m_BeatListLen, false);
}

std::size_t Music::Tempo::GetBeatValue(std::size_t idx) {
    const auto beatIdx = idx % m_BeatListLen;
    return m_BeatList.at(beatIdx);
}

std::size_t Music::Tempo::GetBeatListLen() {
    return m_BeatListLen;
}

void Music::Tempo::Update(
    const std::size_t musicPlaytTime,
    const std::size_t triggerOffset,
    const std::size_t MusicLoopCounter
) {
    if (m_IsPause) {
        return;
    }

    if (m_CurrentBeatLopTimes != MusicLoopCounter) {
        m_CurrentBeatLopTimes = MusicLoopCounter;
        LopReset();
    }

    if (m_CurrentBeatIdx == m_BeatList.size() - 1) {
        return;
    }

    if (m_BeatList.back() < musicPlaytTime) {
        return;
        throw std::runtime_error("out of range");
    }

    if (m_BeatList.at(m_CurrentBeatIdx) + triggerOffset < musicPlaytTime) {
        m_IsBeatSwitch = true;
        m_CurrentBeatIdx++;
    }
}

std::vector<std::size_t> Music::Tempo::m_BeatList;
std::vector<bool>        Music::Tempo::m_IsBeatClick;
std::size_t              Music::Tempo::m_BeatListLen = 0;
std::size_t              Music::Tempo::m_CurrentBeatIdx = 0;
std::size_t              Music::Tempo::m_CurrentBeatLopTimes = 0;

bool Music::Tempo::m_IsBeatSwitch = false;
bool Music::Tempo::m_IsPause = false;
