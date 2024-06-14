#include "Settings/Animation.h"

#include "Util/Logger.hpp"
#include "Util/Time.hpp"

#include "Settings/ToolBoxs.h"
#include "Settings/Window.hpp"

Animation::Animation(const glm::vec2& animationPosition)
    : m_AnimationPosition(animationPosition) {
    m_MoveAnimation = {
      {0, Window::TileWidth * Window::Scale / 1.2f},
      {Window::TileWidth * Window::Scale / 3.0f,
       Window::TileWidth * Window::Scale / 1.2f},
      {-Window::TileWidth * Window::Scale / 4.8f,
       Window::TileWidth * Window::Scale / 1.2f},
      {-Window::TileWidth * Window::Scale / 3.0f,
       Window::TileWidth * Window::Scale / 1.2f},
      {0.0f, 0.0f},
      {0, -Window::TileWidth * Window::Scale / 1.2f},
      {Window::TileWidth * Window::Scale / 1.2f,
       Window::TileWidth * Window::Scale / 1.2f},
      {0, Window::TileWidth * Window::Scale / 1.2f},
      {-Window::TileWidth * Window::Scale / 1.2f,
       Window::TileWidth * Window::Scale / 1.2f}
    };
    m_AnimationZIndex = CalculateZIndex(animationPosition);
}

void Animation::MoveByTime(
    const Util::ms_t duringTimeMs,
    const glm::vec2& destination,
    const uint16_t   direction
) {
    m_AnimationData.push_back(
        {duringTimeMs,
         destination,
         (destination - m_AnimationPosition) / duringTimeMs,
         m_MoveAnimation[direction] / duringTimeMs,
         true}
    );
}

void Animation::MoveByTime(
    const Util::ms_t duringTimeMs,
    const glm::vec2& destination
) {
    MoveByTime(duringTimeMs, destination, 4);
}

bool Animation::UpdateAnimation() {
    Util::ms_t elapsedTimeMs = Util::Time::GetElapsedTimeMs();
    bool       flag = false;
    // quick pass
    if (m_AnimationData.size() >= 2) {
        m_AnimationPosition = m_AnimationData.front().destination;
        m_AnimationData.pop_front();
        m_AnimationZIndex = CalculateZIndex(m_AnimationPosition);
        return true;
    }

    if (!m_AnimationData.empty()) {
        flag = true;
        auto data = m_AnimationData.front();
        if (data.isFirst) {
            m_AnimationStartTimeMs = elapsedTimeMs;
            m_AnimationLastTimeMs = elapsedTimeMs;
            m_AnimationData.front().isFirst = false;
            data = m_AnimationData.front();
        }

        Util::ms_t passTimeMs = elapsedTimeMs - m_AnimationStartTimeMs;
        Util::ms_t lastTimeMs = elapsedTimeMs - m_AnimationLastTimeMs;
        m_AnimationLastTimeMs = elapsedTimeMs;

        if (passTimeMs >= data.duringTimeMs) {
            m_AnimationPosition = data.destination;
            m_AnimationData.pop_front();
        } else {
            if (passTimeMs <= data.duringTimeMs / 2) {
                m_AnimationPosition += data.stepDirection * lastTimeMs;
            } else {
                m_AnimationPosition -= data.stepDirection * lastTimeMs;
            }
            m_AnimationPosition += data.step * lastTimeMs;
        }
    }
    m_AnimationZIndex = CalculateZIndex(m_AnimationPosition);
    return flag;
}

bool Animation::IsAnimating() {
    return !m_AnimationData.empty();
}

glm::vec2 Animation::GetAnimationPosition() {
    return m_AnimationPosition;
}

float Animation::GetAnimationZIndex() {
    return m_AnimationZIndex;
}

void Animation::UpdateGamePosition(const glm::vec2& gamePosition) {
    SetAnimationStop();
    m_AnimationPosition = gamePosition;
    m_AnimationZIndex = CalculateZIndex(m_AnimationPosition);
}

void Animation::SetAnimationPosition(const glm::vec2& position) {
    SetAnimationStop();
    m_AnimationPosition = position;
    m_AnimationZIndex = CalculateZIndex(m_AnimationPosition);
}

Util::ms_t Animation::GetAnimationStartMs() {
    return m_AnimationStartTimeMs;
}

Util::ms_t Animation::GetAnimationDuringTimeMs() {
    return m_AnimationData.front().duringTimeMs;
}

glm::vec2 Animation::GetAnimationDestination() {
    return m_AnimationData.front().destination;
}

void Animation::SetAnimationStop() {
    m_AnimationData.clear();
}

float Animation::CalculateZIndex(const glm::vec2& position) {
    // Zindex = y+0.33
    return ToolBoxs::PosToGamePos(
               {0, position.y - Window::TileWidth - Window::TileWidth}
    )
        .y;
}
