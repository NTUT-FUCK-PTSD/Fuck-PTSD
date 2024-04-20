//
// Created by adven on 2024/3/27.
//
#include "Music/Music.h"

Music::Player::Player() {
    m_soloud.init();

    m_display.setOffset(m_DisplayOffset);
    m_display.setTriggerRange(m_DisplayRange);
    m_display.setMusicSpeed(m_currentSpeed);
    m_display.setHeartBeatTime(m_DisplayHeartBeatDurationTime);

    m_tempo.setOffset(m_TempoOffset);
    m_tempo.setRange(m_TempoRange);
    m_tempo.setShowBeat(isShowHeartBeat);
    m_tempo.setMusicSpeed(m_currentSpeed);
}

Music::Player::~Player() {
    m_soloud.deinit();
}

void Music::Player::setSpeed(float musicSpeed) {
    m_currentSpeed = musicSpeed;
    m_soloud.setRelativePlaySpeed(m_musicHandle, musicSpeed);
}
void Music::Player::speedUp(float musicSpeed) {
    m_soloud.setRelativePlaySpeed(m_musicHandle, m_currentSpeed + musicSpeed);
    m_currentSpeed = m_currentSpeed + musicSpeed;
}

std::size_t Music::Player::getTempoIndex() {
    return m_tempo.getTempoIndex();
}

std::size_t Music::Player::getTempoTime() {
    return m_tempo.getTempo();
}

void Music::Player::playMusic(const std::string &musicPath) {
    m_music = std::make_shared<SoLoud::Wav>();
    m_music->load(musicPath.c_str());
    m_musicHandle = m_soloud.play(*m_music);
}
void Music::Player::playMusic(const std::string &musicPath,
                              bool setMusicLooping) {
    m_music = std::make_shared<SoLoud::Wav>();
    m_music->load(musicPath.c_str());
    m_music->setLooping(setMusicLooping);
    m_musicHandle = m_soloud.play(*m_music);
}

void Music::Player::skipToTargetTime(float time) {
    m_soloud.seek(m_musicHandle, time);
}

std::shared_ptr<GameElement> Music::Player::getGameObject() {
    m_MusicObject->AddChild(m_display.getGameElement());
    m_MusicObject->AddChild(m_rhythmIndicator.GetGameElement());

    m_MusicObject->SetVisible(false);
    return m_MusicObject;
}

void Music::Player::Update() {
    const std::size_t musicLength = m_music->getLength() * 1000;
    const std::size_t CircleTime = m_soloud.getStreamTime(m_musicHandle) * 1000;
    const std::size_t CurrentMusicTime = CircleTime % musicLength;

    m_tempo.setMusicCurrentTime(CurrentMusicTime * m_currentSpeed);
    m_tempo.Update();

    m_display.setTriggerTime(m_tempo.getTempo());
    m_display.setCurrentMusicTime(CurrentMusicTime * m_currentSpeed);
    m_display.Update();

    m_rhythmIndicator.Update();
};

void Music::Player::readTempoFile(const std::string &path) {
    m_tempo.readTempoFile(path);

    const std::vector<std::size_t> tempoList = m_tempo.GetTempoTriggerList();
    m_rhythmIndicator.SetTempoTriggerList(tempoList);
}
