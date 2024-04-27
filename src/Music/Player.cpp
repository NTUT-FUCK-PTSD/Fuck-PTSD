#include "Music/Player.h"

void Music::Player::Init() {
    m_MusicSystem.init();
}

void Music::Player::PlayMusic(const std::string& path, bool loop) {
    // play main background music

    m_Wav->load(path.c_str());
    m_Wav->setLooping(loop);
    m_MusicHandle = m_MusicSystem.play(*m_Wav);
}

void Music::Player::PlayMusic(
    const std::string& path,
    bool               loop,
    float              volume,
    float              speed
) {
    m_Wav->load(path.c_str());
    m_Wav->setLooping(loop);
    m_MusicHandle = m_MusicSystem.play(*m_Wav);
    m_MusicSystem.setVolume(m_MusicHandle, volume);
    m_MusicSystem.setRelativePlaySpeed(m_MusicHandle, speed);
}

void Music::Player::StopMusic() {
    m_MusicSystem.stop(m_MusicHandle);
}

void Music::Player::Shutdown() {
    m_MusicSystem.stopAll();
    m_MusicSystem.deinit();
}

void Music::Player::SetVolume(float volume) {
    m_MusicSystem.setVolume(m_MusicHandle, volume);
}

void Music::Player::SetSpeed(float speed) {
    m_MusicSystem.setRelativePlaySpeed(m_MusicHandle, speed);
}

std::size_t Music::Player::LoopCounter() {
    return m_MusicSystem.getLoopCount(m_MusicHandle);
}

float Music::Player::GetMusicTime() {
    return m_MusicSystem.getStreamTime(m_MusicHandle);
}

float Music::Player::GetMusicLength() {
    return m_Wav->getLength();
}

std::shared_ptr<SoLoud::Wav> Music::Player::m_Wav =
    std::make_shared<SoLoud::Wav>();

SoLoud::Soloud Music::Player::m_MusicSystem;
SoLoud::Speech Music::Player::m_Speech;
SoLoud::handle Music::Player::m_MusicHandle;
