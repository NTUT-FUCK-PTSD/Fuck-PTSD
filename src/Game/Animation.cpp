#include "Animation.h"

void Animation::MoveByTime(const unsigned long &duringTimeMs,
                           const glm::vec2 &destination,
                           const uint16_t &direction) {
    if (m_IsAnimating) {
        m_AnimationPosition = m_AnimationDestination;
        UpdateAnimation();
    }
    m_AnimationStartMs = Util::Time::GetElapsedTimeMs();
    m_AnimationDuringTimeMs = duringTimeMs;
    m_AnimationDestination = destination;
    m_IsAnimating = true;
    m_AnimationDirection = direction;
}

void Animation::UpdateAnimation() {
    if (m_IsAnimating) {
        unsigned long passTimeMs =
            Util::Time::GetElapsedTimeMs() - m_AnimationStartMs;
        if (passTimeMs > m_AnimationDuringTimeMs ||
            m_AnimationPosition == m_AnimationDestination) {
            m_AnimationPosition = m_AnimationDestination;
            m_IsAnimating = false;
        }
        else {
            if (passTimeMs <= m_AnimationDuringTimeMs / 2.0f) {
                float ratio = (float)passTimeMs / (m_AnimationDuringTimeMs / 2);
                m_AnimationPosition +=
                    m_MoveAnimation[m_AnimationDirection] * ratio;
            }
            else {
                float ratio =
                    (float)(passTimeMs + (m_AnimationDuringTimeMs / 2)) /
                    (m_AnimationDuringTimeMs / 2);
                m_AnimationPosition -=
                    m_MoveAnimation[m_AnimationDirection] * (1.0f - ratio);
            }
            float ratio = (float)passTimeMs / m_AnimationDuringTimeMs;
            glm::vec2 move = m_AnimationDestination - m_AnimationPosition;
            m_AnimationPosition += move * ratio;
        }
    }
}
