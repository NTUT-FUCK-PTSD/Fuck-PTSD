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

music::music(const std::string &path, const double speech,
             const bool modulate) {

    // init sdl and include audio plugin
    //    SDL_Init(SDL_INIT_AUDIO);
    //
    //    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_CHANNELS,
    //                  MIX_DEFAULT_FORMAT, CHUNK_SIZE);
    //
    //    Mix_QuerySpec(&m_AudioFrequency, &m_AudioFormat,
    //    &m_AudioChannelCount);
    //
    //    m_AudioAllocatedMixChannelsCount = Mix_AllocateChannels(MIX_CHANNELS);

    Mix_Chunk *chunk = Mix_LoadWAV(
        "/Users/chenshiang/Desktop/I-Love-PTSD/assets/music/app.wav");
    LOG_DEBUG(SDL_GetError());
    //    Mix_Music *music = Mix_LoadMUS(
    //        "/Users/chenshiang/Desktop/I-Love-PTSD/assets/music/app.wav");
    const double initialSpeed = speech;
    //    const float initialSpeed = argc > 2 ? atof(argv[2]) : 1.0;
    //    const bool modulate = argc > 3 ? atoi(argv[3]) : false;

    float speed = initialSpeed;
    if (chunk != NULL) {
        const int channel =
            Mix_PlayChannelTimed(-1, chunk, -1, EXAMPLE_DURATION);
        setupPlaybackSpeedEffect(chunk, speed, channel, true);
        std::cout << "Looping for 8 seconds..." << std::endl;

        // while looping, change pitch dynamically
        if (modulate)
            while (SDL_GetTicks() < EXAMPLE_DURATION)
                speed = initialSpeed + 0.25 * sin(0.001 * SDL_GetTicks());
        else
            //            SDL_Delay(EXAMPLE_DURATION);

            std::cout << "Finished." << std::endl;
    }
    else
        std::cout << "No data." << std::endl;

    //    Mix_FreeChunk(chunk);
    //    Mix_CloseAudio();
    //    Mix_Quit();
    //    SDL_Quit();
}

void music::setupPlaybackSpeedEffect(const Mix_Chunk *const chunk,
                                     const float &speed, int channel, bool loop,
                                     bool trySelfHalt) {
    // select the register function for the current audio format and register
    // the effect using the compatible handlers
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
