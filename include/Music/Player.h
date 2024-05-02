#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <memory>
#include <string>

#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_thread.h"
#include "soloud_wav.h"

namespace Music {
class Player {
public:
    static void Init();

    static void PlayMusic(const std::string& path, bool loop = false);
    static void PlayMusic(
        const std::string& path,
        bool               loop,
        float              volume,
        float              speed
    );

    static void PauseMusic(bool state);

    static void StopMusic();

    static void Shutdown();

    static void SetVolume(float volume);

    static void SetSpeed(float speed);

    static std::size_t LoopCounter();

    static float GetMusicTime();

    static float GetMusicLength();

private:
    static SoLoud::Soloud               m_MusicSystem;
    static std::shared_ptr<SoLoud::Wav> m_Wav;
    static SoLoud::Speech               m_Speech;
    static SoLoud::handle               m_MusicHandle;
};
}  // namespace Music

#endif  // MUSIC_PLAYER_H
