//
// Created by adven on 2024/3/27.
//

#ifndef FUCK_PTSD_DISPLAY_H
#define FUCK_PTSD_DISPLAY_H

#include <iostream>

#include "GameElement.h"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"

class Display final {
public:
    explicit Display();
    ~Display();

    void setBeatSpeed(std::size_t beatSpeed) { m_HeartInterval = beatSpeed; };

    void Update();

    std::shared_ptr<GameElement> getGameElement() const { return m_BeatHeart; };

    void setMusicSpeed(float speed) {m_MusicSpeed = speed; };
    void setOffset(int16_t offset) {m_offset = offset; };
    void setTriggerTime(std::size_t time) { m_triggerTime = time; };
    void setCurrentMusicTime(std::size_t time) { m_CurrentMusicTime = time + m_offset; };
    void setTriggerRange(std::size_t range) { m_range = range; };

private:
    std::string m_HeartImagePath = ASSETS_DIR "/gui/TEMP_beat_heart.png";

    float m_MusicSpeed = 1.0f;

    std::size_t m_triggerTime = 0;
    std::size_t m_CurrentMusicTime = 0;
    int16_t m_offset = 0;
    std::size_t m_range = 100;

    glm::vec2 m_Scale = {3, 3};
    glm::vec2 m_Position = {0, -300};
    std::size_t m_ZIndex = 50;
    std::size_t m_HeartInterval = 10;

    std::shared_ptr<SpriteSheet> m_TempoHeartImage;
    std::shared_ptr<GameElement> m_BeatHeart = std::make_shared<GameElement>();
};

#endif // FUCK_PTSD_DISPLAY_H
