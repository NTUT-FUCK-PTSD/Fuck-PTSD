//
// Created by adven on 2024/3/27.
//

#ifndef FUCK_PTSD_MUSIC_H
#define FUCK_PTSD_MUSIC_H

#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_thread.h"
#include "soloud_wav.h"
#include <iostream>

#include "Tempo.h"

class MusicSystem final {
public:
    explicit MusicSystem();
    ~MusicSystem();

    void setEnable();

    void playMusic(const std::string &musicPath);

    void playMusic(const std::string &musicPath, bool setMusicLooping);

    // let music to this speed
    void setSpeed(float musicSpeed);

    // plus the speed to current speed, and play.
    void speedUp(float musicSpeed);

    void skipToTargetTime(float time);

    void clickEvent() {
        m_tempo.keyBoardClick();
    };

    void readTempoFile(const std::string &path) {
        m_tempo.readTempoFile(path);
    };

    bool TempoTrigger() {
        return m_tempo.canBeClick(100);
    }

    void Update() {
        std::size_t musicLength =  m_music->getLength() * 1000;
        std::size_t currentTime = m_soloud.getStreamTime(m_musicHandle) * 1000;
        m_tempo.UpdateTime(currentTime % musicLength);
    };

private:
    float m_currentSpeed = 1.0f;

    Tempo m_tempo;

    SoLoud::handle m_musicHandle;

    SoLoud::Soloud m_soloud; // SoLoud engine core
    SoLoud::Speech m_speech; // A sound source (speech, in this case)
    std::shared_ptr<SoLoud::Wav> m_music;
};

#endif // FUCK_PTSD_MUSIC_H
