//
// Created by adven on 2024/3/27.
//
#include "Music/Music.h"

MusicSystem::MusicSystem() {
    m_soloud.init();

    m_display.setOffset(m_DisplayOffset);
    m_display.setTriggerRange(m_DisplayRange);

    m_tempo.setOffset(m_TempoOffset);
    m_tempo.setRange(m_TempoRange);
    m_tempo.setShowBeat(isShowHeartBeat);
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

std::shared_ptr<GameElement> MusicSystem::getGameObject() {
    m_MusicObject->AddChild(m_display.getGameElement());

    m_MusicObject->SetVisible(false);
    return m_MusicObject;
}

void MusicSystem::Update()  {
    const std::size_t musicLength =  m_music->getLength() * 1000;
    const std::size_t CircleTime = m_soloud.getStreamTime(m_musicHandle) * 1000;
    const std::size_t CurrentMusicTime = CircleTime % musicLength;

    m_tempo.setMusicCurrentTime(CurrentMusicTime);
    m_tempo.Update();

    m_display.setTriggerTime(m_tempo.getTriggerTime());
    m_display.setCurrentMusicTime(CurrentMusicTime);
    m_display.Update();
};
