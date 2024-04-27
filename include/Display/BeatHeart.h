#ifndef BEATHEART_H
#define BEATHEART_H

#include <memory>
#include <string>

#include "Util/GameObject.hpp"

#include "GameElement.h"
#include "Settings/GameElement.h"
#include "Settings/SpriteSheet.hpp"
#include "Settings/Window.hpp"
#include "SpriteSheet.hpp"

namespace Display {
class BeatHeart final {
public:
    static void Init();

    static void SwitchHeart(const std::size_t duringTime);

    static std::shared_ptr<GameElement> GetGameElement();

    static void Update();

private:
    static std::string m_HeartImagePath;

    static glm::vec2 m_Position;

    static glm::vec2 m_Scale;

    static float m_ZIndex;

    static std::size_t m_AfterSwitchTime;

    static std::shared_ptr<SpriteSheet> m_HeartImage;

    static std::shared_ptr<GameElement> m_GameElement;
};
}  // namespace Display

#endif  // BEATHEART_H
