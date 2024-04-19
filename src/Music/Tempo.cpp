//
// Created by adven on 2024/3/27.
//
#include "Music/Tempo.h"
#include "Util/Logger.hpp"

Music::Tempo::Tempo() {}

Music::Tempo::~Tempo() {}

void Music::Tempo::readTempoFile(const std::string &txtFilePath) {
    std::ifstream txtTempoFile(txtFilePath);

    if (!txtTempoFile.is_open()) {
        LOG_ERROR("fuck it can not open this file");
        return;
    }

    std::string line;
    std::getline(txtTempoFile, line);

    m_tempoList = txtToVector(line, ',');

    // 关闭文件流
    txtTempoFile.close();
}

std::vector<std::size_t> Music::Tempo::txtToVector(const std::string &line,
                                            const char splitChar) {
    std::stringstream ss(line);
    std::string item;
    std::size_t transform = 0;
    std::vector<std::size_t> elems;
    while (std::getline(ss, item, splitChar)) {
        transform = std::stoi(item);
        elems.push_back(std::move(transform));
    }

    m_tempoListLength = elems.size();
    return elems;
}

//bool Music::Tempo::canBeClick() {
//    const std::size_t tempoIndex = m_tempoIndex;
//
//    const std::size_t triggerLower = m_tempoList[tempoIndex] - m_range;
//    const std::size_t triggerUpper = m_tempoList[tempoIndex] + m_range;
//
//    // if yes = true, no = false;
//    return m_duringTime >= triggerLower && m_duringTime <= triggerUpper;
//}

bool Music::Tempo::canBeClick() {

    auto tempoIndex = m_tempoIndex + m_punishTimes;

    //    if (m_isWrongTimeClick == true) {
    //        tempoIndex -= 1;
    //    }

    //    LOG_INFO(m_tempoList[tempoIndex]);
    //    LOG_DEBUG(m_duringTime);

    if (m_duringTime >= (m_tempoList[tempoIndex] - m_range) * m_MusicSpeed &&
        m_duringTime <= (m_tempoList[tempoIndex] + m_range) * m_MusicSpeed) {
        return true;
    }
    return false;
}

std::size_t Music::Tempo::getTempo() {
    return m_tempoList.empty() ? 0 : m_currentTempoTime;
};

void Music::Tempo::Update() {
    m_currentTempoTime = m_tempoList.empty()
                             ? 0
                             : m_tempoList[m_currentTempoIndex] * m_MusicSpeed;

    //    LOG_INFO(m_currentTempoIndex);
    UpdateTempoIndex();
    UpdateTime();
}

void Music::Tempo::keyBoardClick() {
    m_punishTimes = m_punishTimes < 1 ? m_punishTimes + 1 : m_punishTimes;

    LOG_INFO(m_tempoIndex);

    if (m_isWrongTimeClick == false) {
        m_tempoIndex++;
    }

    m_isWrongTimeClick = true;
};

void Music::Tempo::UpdateTime() {
    if (m_tempoList.empty()) {
        return;
    }

    // song of looping end time, the bug
    if (m_tempoIndex == 0 && m_duringTime > 5000) {
        return;
    }

    //    LOG_INFO(m_isWrongTimeClick);

    // getTempo return value
    if (m_duringTime >=
            (m_tempoList[m_currentTempoIndex] - m_range) * m_MusicSpeed &&
        m_duringTime <=
            (m_tempoList[m_currentTempoIndex] + m_range) * m_MusicSpeed) {
        return;
    }

    m_currentTempoIndex++;
    m_isWrongTimeClick = false;

    if (m_duringTime >= (m_tempoList[m_tempoIndex] - m_range) * m_MusicSpeed &&
        m_duringTime <= (m_tempoList[m_tempoIndex] + m_range) * m_MusicSpeed) {
        return;
    }
    else if (m_duringTime <=
                 (m_tempoList[m_tempoIndex + 1] - m_range) * m_MusicSpeed &&
             m_duringTime <=
                 (m_tempoList[m_tempoIndex + 1] + m_range) * m_MusicSpeed) {
        return;
    }

    m_punishTimes = m_punishTimes == 0 ? m_punishTimes : m_punishTimes - 1;
    m_tempoIndex++;

    //    if (isShowHeartBeat) {
    //        LOG_DEBUG(m_punishTimes);
    //        LOG_INFO(m_duringTime);
    //        LOG_INFO(m_currentTempoTime);
    //    }
}

void Music::Tempo::UpdateTempoIndex() {
    m_tempoIndex = m_tempoIndex + 1 >= m_tempoListLength ? 0 : m_tempoIndex;
    m_currentTempoIndex =
        m_currentTempoIndex + 1 >= m_tempoListLength ? 0 : m_currentTempoIndex;
}

std::size_t Music::Tempo::getTempoIndex() const{
    return m_currentTempoIndex;
}
