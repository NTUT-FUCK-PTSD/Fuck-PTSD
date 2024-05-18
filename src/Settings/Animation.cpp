#include "Settings/Animation.h"

#include "Util/Time.hpp"

#include "Settings/ToolBoxs.h"
#include "Settings/Window.hpp"

Animation::Animation(const glm::vec2& animationPosition)
    : m_AnimationDestination(animationPosition),
      m_AnimationPosition(animationPosition) {
    m_MoveAnimation = {
      {0, Window::TileWidth * Window::Scale / 3.0f},
      {Window::TileWidth * Window::Scale / 7.5f,
       Window::TileWidth * Window::Scale / 3.0f},
      {-Window::TileWidth * Window::Scale / 12.0f,
       Window::TileWidth * Window::Scale / 3.0f},
      {-Window::TileWidth * Window::Scale / 7.5f,
       Window::TileWidth * Window::Scale / 3.0f},
      {0.0f, 0.0f},
      {0, -Window::TileWidth * Window::Scale / 3.0f},
      {Window::TileWidth * Window::Scale / 3.0f,
       Window::TileWidth * Window::Scale / 3.0f},
      {0, Window::TileWidth * Window::Scale / 3.0f},
      {-Window::TileWidth * Window::Scale / 3.0f,
       Window::TileWidth * Window::Scale / 3.0f}
    };
    m_AnimationZIndex = CalculateZIndex(animationPosition);
}

void Animation::MoveByTime(
    const unsigned long duringTimeMs,
    const glm::vec2&    destination,
    const uint16_t      direction
) {
    if (m_IsAnimatingInternal) {
        m_AnimationPosition = m_AnimationDestination;
        UpdateAnimation(true);
    }
    m_AnimationStartMs = Util::Time::GetElapsedTimeMs();
    m_AnimationDuringTimeMs = duringTimeMs;
    m_AnimationDestination = destination;
    m_IsAnimatingInternal = true;
    m_IsAnimating = true;
    m_AnimationDirection = direction;
}

void Animation::MoveByTime(
    const unsigned long duringTimeMs,
    const glm::vec2&    destination
) {
    if (m_IsAnimatingInternal) {
        m_AnimationPosition = m_AnimationDestination;
        UpdateAnimation(false);
    }
    m_AnimationStartMs = Util::Time::GetElapsedTimeMs();
    m_AnimationDuringTimeMs = duringTimeMs;
    m_AnimationDestination = destination;
    m_IsAnimatingInternal = true;
    m_IsAnimating = true;
}

void Animation::UpdateAnimation(const bool isDirection) {
    if (m_IsAnimatingInternal) {
        unsigned long passTimeMs = Util::Time::GetElapsedTimeMs()
                                   - m_AnimationStartMs;

        if (passTimeMs > m_AnimationDuringTimeMs
            || ((m_AnimationPosition == m_AnimationDestination) && !isDirection
            )) {
            m_AnimationPosition = m_AnimationDestination;
            m_IsAnimatingInternal = false;
        } else {
            if (isDirection) {
                if (passTimeMs <= m_AnimationDuringTimeMs / 2.0f) {
                    float ratio = (float)passTimeMs
                                  / (m_AnimationDuringTimeMs / 2.0f);
                    m_AnimationPosition += m_MoveAnimation[m_AnimationDirection]
                                           * ratio;
                } else {
                    float ratio = (float)(passTimeMs
                                          + (m_AnimationDuringTimeMs / 2.0f))
                                  / (m_AnimationDuringTimeMs / 2.0f);
                    m_AnimationPosition -= m_MoveAnimation[m_AnimationDirection]
                                           * (1.0f - ratio);
                }
            }
            float     ratio = (float)passTimeMs / m_AnimationDuringTimeMs;
            glm::vec2 move = m_AnimationDestination - m_AnimationPosition;
            m_AnimationPosition += move * ratio;
        }
    }
    m_AnimationZIndex = CalculateZIndex(m_AnimationPosition);
}

bool Animation::IsAnimating() {
    if (!m_IsAnimatingInternal && m_IsAnimating) {
        m_IsAnimating = false;
        return true;
    }
    return m_IsAnimating;
}

glm::vec2 Animation::GetAnimationPosition() {
    return m_AnimationPosition;
}

float Animation::GetAnimationZIndex() {
    return m_AnimationZIndex;
}

void Animation::UpdateGamePosition(const glm::vec2& gamePosition) {
    m_IsAnimating = false;
    m_IsAnimatingInternal = false;
    m_AnimationPosition = ToolBoxs::GamePostoPos(gamePosition);
    m_AnimationDestination = m_AnimationPosition;
    m_AnimationZIndex = CalculateZIndex(m_AnimationPosition);
}

unsigned long Animation::GetAnimationStartMs() {
    return m_AnimationStartMs;
}

unsigned long Animation::GetAnimationDuringTimeMs() {
    return m_AnimationDuringTimeMs;
}

glm::vec2 Animation::GetAnimationDestination() {
    return m_AnimationDestination;
}

void Animation::SetAnimationStop() {
    m_IsAnimating = false;
    m_IsAnimatingInternal = false;
}

float Animation::CalculateZIndex(const glm::vec2& position) {
    // Zindex = y+0.33
    return ToolBoxs::PosToGamePos(
               {0, position.y - Window::TileWidth - Window::TileWidth}
    )
        .y;
}
