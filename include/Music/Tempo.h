//
// Created by adven on 2024/3/27.
//

#ifndef FUCK_PTSD_TEMPO_H
#define FUCK_PTSD_TEMPO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Util/Logger.hpp"

class Tempo final {
public:
    explicit Tempo();
    ~Tempo();

    // must read one line in file, it not be '\n'
    void readTempoFile(const std::string& txtFilePath);

    bool canBeClick(std::size_t offset);

    void keyBoardClick() {
        m_tempoIndex++;
    };

    std::size_t getTriggerTime() {
        if (m_tempoList.empty()) { return 0; }
        return m_tempoList[m_tempoIndex];
    };

    void UpdateTime();

    void UpdateTime(float time);
private:
//    void listenBeat();
    std::vector<std::size_t> txtToVector(const std::string& line, const char splitChar);

    bool isTrigger = false;

    float m_duringTime = 0.0f;
    std::size_t m_offset = 1000;// (ms)

    std::size_t m_tempoIndex = 0;
    std::size_t m_tempoListLength = 0;
    std::vector<std::size_t> m_tempoList;

};

#endif // FUCK_PTSD_TEMPO_H
