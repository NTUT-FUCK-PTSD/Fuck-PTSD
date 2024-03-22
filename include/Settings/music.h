//
// Created by 陳世昂 on 2024/3/13.
//

#ifndef FUCK_PTSD_MUSIC_H
#define FUCK_PTSD_MUSIC_H

#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>

class music final {
public:
    explicit music(const std::string &path, const double speech,
                   const bool modulate);

    void play();

private:
    void setupPlaybackSpeedEffect(const Mix_Chunk *const chunk,
                                  const float &speed, int channel,
                                  bool loop = false, bool trySelfHalt = false);

    struct MusicDeleter_Mix {
        void operator()(Mix_Chunk *music) { Mix_FreeChunk(music); }
    };

    Uint16 m_AudioFormat;    // current audio format constant
    int m_AudioFrequency;    // frequency rate of the current audio format
    int m_AudioChannelCount; // number of channels of the current audio format
    int m_AudioAllocatedMixChannelsCount; // number of mix channels allocated

    std::unique_ptr<Mix_Chunk, MusicDeleter_Mix> m_Audio;

    std::string path;
    double speech;
    bool modulate;
};
#endif // FUCK_PTSD_MUSIC_H
