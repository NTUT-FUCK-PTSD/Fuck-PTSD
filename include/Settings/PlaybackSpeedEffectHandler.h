//
// Created by 陳世昂 on 2024/3/14.
//

#ifndef FUCK_PTSD_PLAYBACKSPEEDEFFECTHANDLER_H
#define FUCK_PTSD_PLAYBACKSPEEDEFFECTHANDLER_H

#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>

template <typename AudioFormatType>
struct PlaybackSpeedEffectHandler {
    const AudioFormatType
        *const chunkData;     // pointer to the chunk sample data (as array)
    const float &speedFactor; // the playback speed factor
    float position;           // current position of the sound, in ms
    const int duration;       // the duration of the sound, in ms
    const int
        chunkSize;   // the size of the sound, as a number of indexes (or sample
                     // points). thinks of this as a array size when using the
                     // proper array type (instead of just Uint8*).
    const bool loop; // flags whether playback should stay looping
    const bool attemptSelfHalting; // flags whether playback should be halted by
                                   // this callback when playback is finished
    bool altered; // true if this playback has been pitched by this handler

    Uint16 audioFormat;    // current audio format constant
    int audioFrequency;    // frequency rate of the current audio format
    int audioChannelCount; // number of channels of the current audio format
    int audioAllocatedMixChannelsCount; // number of mix channels allocated

    PlaybackSpeedEffectHandler(const Mix_Chunk &chunk, const float &speed,
                               bool loop, bool trySelfHalt, int audioFrequency,
                               int audioChannelCount,
                               int audioAllocatedMixChannelsCount,
                               Uint16 audioFormat)
        : chunkData(reinterpret_cast<AudioFormatType *>(chunk.abuf)),
          speedFactor(speed),
          position(0),
          duration(computeChunkLengthMillisec(chunk.alen)),
          chunkSize(chunk.alen / formatSampleSize(audioFormat)),
          loop(loop),
          attemptSelfHalting(trySelfHalt),
          altered(false),
          audioChannelCount(audioChannelCount),
          audioFormat(audioFormat),
          audioFrequency(audioFrequency),
          audioAllocatedMixChannelsCount(audioAllocatedMixChannelsCount) {}

    static inline Uint16 formatSampleSize(Uint16 format) {
        return (format & 0xFF) / 8;
    }

    // Get chunk time length (in ms) given its size and current audio format
    int computeChunkLengthMillisec(int chunkSize) {
        const Uint32 points =
            chunkSize / formatSampleSize(
                            audioFormat); // bytes / samplesize == sample points
        const Uint32 frames =
            (points /
             audioChannelCount); // sample points / channels == sample frames
        return ((frames * 1000) /
                audioFrequency); // (sample frames * 1000) / frequency == play
                                 // length, in ms
    }

    // processing function to be able to change chunk speed/pitch.
    void modifyStreamPlaybackSpeed(int mixChannel, void *stream, int length) {
        AudioFormatType *buffer = static_cast<AudioFormatType *>(stream);
        const int bufferSize =
            length / sizeof(AudioFormatType); // buffer size (as array)
        const float speedFactor =
            this->speedFactor; // take a "snapshot" of speed factor

        // if there is still sound to be played
        if (position < duration || loop) {
            const float delta =
                            1000.0 /
                            audioFrequency,   // normal duration of each sample
                vdelta = delta * speedFactor; // virtual stretched duration,
                                              // scaled by 'speedFactor'

            // if playback is unaltered and pitch is required (for the first
            // time)
            if (!altered && speedFactor != 1.0f)
                altered = true; // flags playback modification and proceed to
                                // the pitch routine.

            if (altered) // if unaltered, this pitch routine is skipped
            {
                for (int i = 0; i < bufferSize; i += audioChannelCount) {
                    const int j = i / audioChannelCount; // j goes from 0 to
                                                         // size/channelCount,
                                                         // incremented 1 by 1
                    const float x =
                        position +
                        j * vdelta; // get "virtual" index. its corresponding
                                    // value will be interpolated.
                    const int k = floor(
                        x /
                        delta); // get left index to interpolate from original
                                // chunk data (right index will be this plus 1)
                    const float prop =
                        (x / delta) - k; // get the proportion of the right
                                         // value (left will be 1.0 minus this)

                    // usually just 2 channels: 0 (left) and 1 (right), but who
                    // knows...
                    for (int c = 0; c < audioChannelCount; c++) {
                        // check if k will be within bounds
                        if (k * audioChannelCount + audioChannelCount - 1 <
                                chunkSize ||
                            loop) {
                            AudioFormatType
                                v0 = chunkData[(k * audioChannelCount + c) %
                                               chunkSize],
                                // v_ = chunkData[((k-1) * channelCount + c) %
                                // chunkSize], v2 = chunkData[((k+2) *
                                // channelCount + c) % chunkSize],
                                v1 = chunkData[((k + 1) * audioChannelCount +
                                                c) %
                                               chunkSize];

                            // put interpolated value on 'data'
                            // buffer[i + c] = (1 - prop) * v0 + prop * v1;  //
                            // linear interpolation
                            buffer[i + c] =
                                v0 +
                                prop * (v1 - v0); // linear interpolation
                                                  // (single multiplication)
                            // buffer[i + c] = v0 + 0.5f * prop * ((prop - 3) *
                            // v0 - (prop - 2) * 2 * v1 + (prop - 1) * v2);  //
                            // quadratic interpolation buffer[i + c] = v0 +
                            // (prop / 6) * ((3 * prop - prop2 - 2) * v_ +
                            // (prop2 - 2 * prop - 1) * 3 * v0 + (prop - prop2 +
                            // 2) * 3 * v1 + (prop2 - 1) * v2);  // cubic
                            // interpolation buffer[i + c] = v0 + 0.5f * prop *
                            // ((2 * prop2 - 3 * prop - 1) * (v0 - v1) + (prop2
                            // - 2 * prop + 1) * (v0 - v_) + (prop2 - prop) *
                            // (v2 - v2));  // cubic spline interpolation
                        }
                        else // if k will be out of bounds (chunk bounds), it
                             // means we already finished; thus, we'll pass
                             // silence
                        {
                            buffer[i + c] = 0;
                        }
                    }
                }
            }

            // update position
            position += (bufferSize / audioChannelCount) * vdelta;

            // reset position if looping
            if (loop)
                while (position > duration)
                    position -= duration;
        }
        else // if we already played the whole sound but finished earlier than
             // expected by SDL_mixer (due to faster playback speed)
        {
            // set silence on the buffer since Mix_HaltChannel() poops out some
            // of it for a few ms.
            for (int i = 0; i < bufferSize; i++)
                buffer[i] = 0;

            if (attemptSelfHalting)
                Mix_HaltChannel(
                    mixChannel); // XXX unsafe call, since it locks audio; but
                                 // no safer solution was found yet...
        }
    }

    // Mix_EffectFunc_t callback that redirects to handler method (handler
    // passed via userData)
    static void mixEffectFuncCallback(int channel, void *stream, int length,
                                      void *userData) {
        static_cast<PlaybackSpeedEffectHandler *>(userData)
            ->modifyStreamPlaybackSpeed(channel, stream, length);
    }

    // Mix_EffectDone_t callback that deletes the handler at the end of the
    // effect usage  (handler passed via userData)
    static void mixEffectDoneCallback(int, void *userData) {
        delete static_cast<PlaybackSpeedEffectHandler *>(userData);
    }

    // function to register a handler to this channel for the next playback.
    static void registerEffect(int channel, const Mix_Chunk &chunk,
                               const float &speed, bool loop, bool trySelfHalt,
                               int audioFrequency, int audioChannelCount,
                               int audioAllocatedMixChannelsCount,
                               Uint16 audioFormat) {
        Mix_RegisterEffect(
            channel, mixEffectFuncCallback, mixEffectDoneCallback,
            new PlaybackSpeedEffectHandler(chunk, speed, loop, trySelfHalt,
                                           audioFrequency, audioChannelCount,
                                           audioAllocatedMixChannelsCount,
                                           audioFormat));
    }
};

#endif // FUCK_PTSD_PLAYBACKSPEEDEFFECTHANDLER_H
