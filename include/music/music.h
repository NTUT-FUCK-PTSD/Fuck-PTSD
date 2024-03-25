//
// Created by adven on 2024/3/24.
//

#ifndef FUCK_PTSD_MUSIC_H
#define FUCK_PTSD_MUSIC_H

#include <iostream>

class MusicSystem final {
public:
    explicit MusicSystem();

    ~MusicSystem();

    // the time that start game.
    // e.g. Time::GetElapsedTimeMs()
    void updateTime(std::size_t time);

    void playMusic(const std::string path);

    void setMusicSpeed();

protected:
    // some functional to use
    std::vector<std::size_t> readTempoFile();

private:
    // start time that playing music.
    std::size_t startTimeMs = 0;

    // during time (ms), that from start playing music to now.
    std::size_t duringTimeMs = 0;

    // music playing speed
    float m_CurrentMusicSpeed = 0.0f;
};

#endif // FUCK_PTSD_MUSIC_H
