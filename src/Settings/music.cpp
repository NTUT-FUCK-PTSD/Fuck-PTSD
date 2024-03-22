//
// Created by 陳世昂 on 2024/3/13.
//

#include "Util/Logger.hpp"
#include <SDL.h>
#include <SDL_mixer.h>

#include "PlaybackSpeedEffectHandler.h"
#include "music.h"

#define CHUNK_SIZE 4096
#define EXAMPLE_DURATION 8000

void music::play() {
    auto chunk = m_Audio.get();

    const double initialSpeed = speech;

    float speed = initialSpeed;

    if (chunk != NULL) {
        const int channel =
            Mix_PlayChannelTimed(-1, chunk, -1, EXAMPLE_DURATION);
        //            Mix_PlayChannel(-1, chunk, -1);
        setupPlaybackSpeedEffect(chunk, speed, channel, true);
        std::cout << "Looping for 8 seconds..." << std::endl;

        // while looping, change pitch dynamically
        if (modulate) {
            while (SDL_GetTicks() < EXAMPLE_DURATION)
                speed = initialSpeed + 0.25 * sin(0.001 * SDL_GetTicks());
        }

        bool running = false;
        SDL_Event event;

        SDL_Delay(1000);

        std::cout << "Finished." << std::endl;
    }
    else
        std::cout << "No data." << std::endl;
}

music::music(const std::string &path, const double speech, const bool modulate)
    : m_Audio(Mix_LoadWAV(
                  "/Users/chenshiang/Desktop/I-Love-PTSD/assets/music/app.wav"),
              music::MusicDeleter_Mix()),
      path(path),
      speech(speech),
      modulate(modulate) {

    //    Mix_Chunk *chunk =

    LOG_DEBUG(SDL_GetError());

    //    Mix_FreeChunk(chunk);
    //    Mix_CloseAudio();
    //    Mix_Quit();
    //    SDL_Quit();
}

void music::setupPlaybackSpeedEffect(const Mix_Chunk *const chunk,
                                     const float &speed, int channel, bool loop,
                                     bool trySelfHalt) {
    // select the register function for the current audio format and
    // register the effect using the compatible handlers
    // XXX is it correct to behave the same way to all S16 and U16 formats?
    // Should we create case statements for AUDIO_S16SYS, AUDIO_S16LSB,
    // AUDIO_S16MSB, etc, individually?
    switch (m_AudioFormat) {
    case AUDIO_U8:
        PlaybackSpeedEffectHandler<Uint8>::registerEffect(
            channel, *chunk, speed, loop, trySelfHalt, m_AudioFrequency,
            m_AudioChannelCount, m_AudioAllocatedMixChannelsCount,
            m_AudioFormat);
        break;
    case AUDIO_S8:
        PlaybackSpeedEffectHandler<Sint8>::registerEffect(
            channel, *chunk, speed, loop, trySelfHalt, m_AudioFrequency,
            m_AudioChannelCount, m_AudioAllocatedMixChannelsCount,
            m_AudioFormat);
        break;
    case AUDIO_U16:
        PlaybackSpeedEffectHandler<Uint16>::registerEffect(
            channel, *chunk, speed, loop, trySelfHalt, m_AudioFrequency,
            m_AudioChannelCount, m_AudioAllocatedMixChannelsCount,
            m_AudioFormat);
        break;
    default:
    case AUDIO_S16:
        PlaybackSpeedEffectHandler<Sint16>::registerEffect(
            channel, *chunk, speed, loop, trySelfHalt, m_AudioFrequency,
            m_AudioChannelCount, m_AudioAllocatedMixChannelsCount,
            m_AudioFormat);
        break;
    case AUDIO_S32:
        PlaybackSpeedEffectHandler<Sint32>::registerEffect(
            channel, *chunk, speed, loop, trySelfHalt, m_AudioFrequency,
            m_AudioChannelCount, m_AudioAllocatedMixChannelsCount,
            m_AudioFormat);
        break;
    case AUDIO_F32:
        PlaybackSpeedEffectHandler<float>::registerEffect(
            channel, *chunk, speed, loop, trySelfHalt, m_AudioFrequency,
            m_AudioChannelCount, m_AudioAllocatedMixChannelsCount,
            m_AudioFormat);
        break;
    }
}
