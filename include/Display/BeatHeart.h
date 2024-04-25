#ifndef BEATHEART_H
#define BEATHEART_H

#include <memory>

#include "Util/GameObject.hpp"

#include "GameElement.h"
#include "SpriteSheet.hpp"

namespace Display {
class BeatHeart : public GameElement {
public:
    explicit BeatHeart();
    virtual ~BeatHeart() = default;

    void Update();

private:
    static std::string m_HeartImagePath;

    static std::shared_ptr<SpriteSheet> m_HeartImage;

    static const glm::vec2 m_Position;

    static const glm::vec2 m_Scale;

    static const float m_ZIndexBeatHeart;
};
}  // namespace Display

#endif  // BEATHEART_H
