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

#include "Display.h"
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

    void clickEvent() { m_tempo.keyBoardClick(); };

    void readTempoFile(const std::string &path) {
        m_tempo.readTempoFile(path);
    };

    bool TempoTrigger() { return m_tempo.canBeClick(); }

    std::shared_ptr<GameElement> getGameObject();

    void Update();

    void setTempoOffset(int16_t offset) { m_TempoOffset = offset; };
    void setTempoRange(std::size_t range) { m_TempoRange = range; };
    void setDisplayOffset(int16_t offset) { m_DisplayOffset = offset; };
    void setDisplayHeartBeatDurationTime(std::size_t time) {
        m_DisplayHeartBeatDurationTime = time;
    };

private:
    float m_currentSpeed = 1.0f;

    Tempo m_tempo;
    Display m_display;

    /* ms */
    int16_t m_TempoOffset = 0;
    std::size_t m_TempoRange = 500;
    /* bool isShowHeartBeat = false; */
    bool isShowHeartBeat = true;
    int16_t m_DisplayOffset = -30;
    std::size_t m_DisplayRange = 100;
    std::size_t m_DisplayHeartBeatDurationTime = 80;

    SoLoud::handle m_musicHandle;

    SoLoud::Soloud m_soloud; // SoLoud engine core
    SoLoud::Speech m_speech; // A sound source (speech, in this case)
    std::shared_ptr<SoLoud::Wav> m_music;

    std::shared_ptr<GameElement> m_MusicObject =
        std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_MUSIC_H
