//
// Created by adven on 2024/4/19.
//
#include "Music/RhythmIndicator.h"

Music::RhythmIndicator::RhythmIndicator()
    : m_redIndicator(std::make_shared<Util::Image>(
          ASSETS_DIR "/gui/TEMP_beat_marker_red.png")),
      m_blueIndicator(std::make_shared<Util::Image>(
          ASSETS_DIR "/gui/TEMP_beat_marker.png")),
      m_greenIndicator(std::make_shared<Util::Image>(
          ASSETS_DIR "/gui/TEMP_beat_marker_green.png")) {
//    m_rhythmIndicator->SetVisible(false);
}

std::shared_ptr<GameElement> Music::RhythmIndicator::GetGameElement() {
    return m_rhythmIndicator;
}

void Music::RhythmIndicator::Update() {}
