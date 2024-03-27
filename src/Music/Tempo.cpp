//
// Created by adven on 2024/3/27.
//
#include "Music/Tempo.h"

Tempo::Tempo() {}

Tempo::~Tempo() {}

void Tempo::readTempoFile(const std::string &txtFilePath) {
    std::ifstream txtTempoFile(txtFilePath);
    LOG_INFO("hello");

    if (!txtTempoFile.is_open()) {
        LOG_ERROR("fuck it can not open this file");
        return;
    }

    std::string line;
    std::getline(txtTempoFile, line);

    m_tempoList = std::move(txtToVector(line, ','));

    // 关闭文件流
    txtTempoFile.close();
}

std::vector<std::size_t> Tempo::txtToVector(const std::string &line,
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

bool Tempo::canBeClick(std::size_t offset) {


    if (m_tempoList[m_tempoIndex] - 100 <= m_duringTime ||
        (m_tempoIndex != 0 &&
         m_tempoList[m_tempoIndex - 1] + 100 >= m_duringTime)) {
        return false;
    }
    return true;
}

void Tempo::UpdateTime(float time) {
    m_duringTime = time;

    if (m_tempoList.empty()) {
        return;
    }

    // TODO: 優化
    //    LOG_DEBUG(m_tempoList[m_tempoIndex]);
    //    LOG_DEBUG(m_tempoIndex);
    //    LOG_DEBUG(m_tempoListLength);
    for (int i = 0; i < m_tempoListLength + 1; i++) {
        if (m_tempoIndex + 1 >= m_tempoListLength) {
            m_tempoIndex = 0;
        }
        if (m_tempoIndex == 0 && m_duringTime > 2000) {
            break;
        }
        else if (m_tempoList[m_tempoIndex] + m_offset < m_duringTime) {
            m_tempoIndex++;
        }
        else {
            break;
        }
    }

    //    LOG_INFO(m_duringTime);
    LOG_INFO(canBeClick(10));
}
