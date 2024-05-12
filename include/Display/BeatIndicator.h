#ifndef I_LOVE_PTSD_BEATINDICATOR_H
#define I_LOVE_PTSD_BEATINDICATOR_H

#include <future>
#include <memory>

#include <Util/Image.hpp>
#include "GameElement.h"

namespace Display {
class BeatIndicator {
public:
    static void Init();

    static void Pause(bool state);

    static std::shared_ptr<GameElement> GetGameElement();

    static void Update();

private:
    static void CreateImage();
    static void GenLeftIndicator(std::size_t counter);
    static void GenRightIndicator(std::size_t counter);
    static void UpdateLeftIndi(
        std::size_t index,
        std::size_t intervalTime,
        std::size_t intervalPixel
    );
    static void UpdateRightIndi(
        std::size_t index,
        std::size_t intervalTime,
        std::size_t intervalPixel
    );

    static bool m_IsPause;

    static std::string m_IndicatorImagePath;
    static glm::vec2   m_Position;
    // static glm::vec2                                 m_Scale;
    // static float                                     m_ZIndex;
    static std::size_t                               m_lastTime;
    static std::size_t                               m_intervalSpace;
    static std::size_t                               m_startBeatIndex;
    static std::size_t                               m_tempoNumber;
    static std::vector<std::shared_ptr<GameElement>> m_IndicatorList;
    static std::vector<std::shared_ptr<GameElement>> m_IndicatorListRight;
    static std::shared_ptr<GameElement>              m_GameElement;
    static std::shared_ptr<Util::Image>              m_blueIndicator;
};
}  // namespace Display

#endif  // I_LOVE_PTSD_BEATINDICATOR_H
