#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>

#include "pch.hpp"  // IWYU pragma: export

#include "Util/Time.hpp"

struct AnimationData {
    Util::ms_t duringTimeMs;
    glm::vec2  destination;
    glm::vec2  step;
    glm::vec2  stepDirection;
    bool       isFirst;
};

class Animation final {
public:
    Animation(const glm::vec2& animationPosition);

    void MoveByTime(
        const Util::ms_t duringTimeMs,
        const glm::vec2& destination
    );

    void MoveByTime(
        const Util::ms_t duringTimeMs,
        const glm::vec2& destination,
        const uint16_t   direction
    );

    bool      UpdateAnimation();
    bool      IsAnimating();
    glm::vec2 GetAnimationPosition();
    float     GetAnimationZIndex();
    void      UpdateGamePosition(const glm::vec2& gamePosition);

    glm::vec2  GetAnimationDestination();
    Util::ms_t GetAnimationStartMs();
    Util::ms_t GetAnimationDuringTimeMs();
    void       SetAnimationStop();

private:
    float CalculateZIndex(const glm::vec2& position);

    std::vector<glm::vec2> m_MoveAnimation;

    std::list<AnimationData> m_AnimationData;

    Util::ms_t m_AnimationStartTimeMs = 0;
    Util::ms_t m_AnimationLastTimeMs = 0;
    glm::vec2  m_AnimationPosition;
    float      m_AnimationZIndex = 0.0f;
};

#endif
