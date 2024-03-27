//
// Created by adven on 2024/3/27.
//
#include "Music/Music.h"

MusicSystem::MusicSystem() {
    m_soloud.init();
}

MusicSystem::~MusicSystem() {
    m_soloud.deinit();
}

void MusicSystem::setSpeed(float musicSpeed) {
    m_currentSpeed = musicSpeed;
    m_soloud.setRelativePlaySpeed(m_musicHandle, musicSpeed);
}
void MusicSystem::speedUp(float musicSpeed) {
    m_soloud.setRelativePlaySpeed(m_musicHandle, m_currentSpeed + musicSpeed);
    m_currentSpeed = m_currentSpeed + musicSpeed;
}

void MusicSystem::playMusic(const std::string &musicPath) {
    m_music = std::make_shared<SoLoud::Wav>();
    m_music->load(musicPath.c_str());
    m_musicHandle = m_soloud.play(*m_music);
}
void MusicSystem::playMusic(const std::string &musicPath, bool setMusicLooping) {
    m_music = std::make_shared<SoLoud::Wav>();
    m_music->load(musicPath.c_str());
    m_music->setLooping(setMusicLooping);
    m_musicHandle = m_soloud.play(*m_music);
}

void MusicSystem::skipToTargetTime(float time) {
    m_soloud.seek(m_musicHandle, time);
}
