//
// Created by adven on 2024/3/27.
//

#ifndef FUCK_PTSD_TEMPO_H
#define FUCK_PTSD_TEMPO_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Util/Logger.hpp"

class Tempo final {
public:
    explicit Tempo();
    ~Tempo();

    // must read one line in file, it not be '\n'
    void readTempoFile(const std::string &txtFilePath);

    bool canBeClick(std::size_t offset);

    void keyBoardClick() {
        m_punishTimes = m_punishTimes < 2 ? m_punishTimes + 1 : m_punishTimes;
    };

    std::size_t getTriggerTime();

    void setShowBeat(bool state) { isShowHeartBeat = state; };
    void setRange(std::size_t range) { m_range = range; };
    void setOffset(int16_t offset) { m_offset = offset; };

    void setMusicCurrentTime(std::size_t time) {
        m_duringTime = time + m_offset;
    };
    void Update();

protected:
    void UpdateTime();
    void UpdateTempoIndex();

private:
    std::vector<std::size_t> txtToVector(const std::string &line,
                                         const char splitChar);

    bool isTrigger = false;
    bool isShowHeartBeat = false;
    std::size_t m_punishTimes = 0;

    std::size_t m_duringTime = 0;
    std::size_t m_range = 500;
    int16_t m_offset = 0; // (ms)

    std::size_t m_tempoIndex = 0;
    std::size_t m_tempoListLength = 0;
    std::vector<std::size_t> m_tempoList;
};

#endif // FUCK_PTSD_TEMPO_H
