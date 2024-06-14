#ifndef FUCK_PTSD_2024_05_13_INDICATORBAR_H
#define FUCK_PTSD_2024_05_13_INDICATORBAR_H

#include <Util/Image.hpp>
#include <memory>
#include "Animation.h"
#include "UGameElement.h"
#include "Util/Time.hpp"

namespace Music {
class IndicatorBar final {
public:
    static void Init();

    static void Pause(bool state);

    static std::shared_ptr<Util::GameElement> GetGameElement();

    static void Update();

    static void Reset();

private:
    using ms_t = std::size_t;
    static constexpr ms_t       TEMPO_TIME_RANGE = 2000;
    static constexpr ms_t       FRAME_UPDATE_MAX = 100;
    static constexpr glm::ivec2 m_CenterPos = {0, -310};

    static void CountTempoNumber();
    static void CountIndicatorIntervalSpace();

    static void CreateImage();
    static void CreateIndicatorLeft();
    static void CreateIndicatorRight();

    static void UpdateTimer();
    static void UpdateIndicatorLeft(
        std::size_t index,
        std::size_t intervalTime,
        std::size_t intervalPixel
    );
    static void UpdateIndicatorRight(
        std::size_t index,
        std::size_t intervalTime,
        std::size_t intervalPixel
    );

    static std::size_t m_TempoNumber;

    static std::size_t m_BeatIndex;

    /**
     * @details This value is the last time the record was updated.
     * @name m_LastRecordTime
     */
    static std::size_t m_LastRecordTime;

    /**
     * @details This value is the time of the interval time between each
     * indicator.
     * @name m_IndicatorIntervalTime
     */
    static std::size_t m_IIT;

    static bool m_IsPause;

    /**
     * @details This value is the number of interval space between each beat
     * indicator.
     * @name m_IndicatorIntervalSpace
     */
    static std::size_t m_IIS;

    /**
     * @details The vector of left indicator.
     */
    static std::vector<std::shared_ptr<Util::GameElement>> m_IndicatLeft;

    static std::vector<std::shared_ptr<Util::GameElement>> m_IndicatRight;

    static std::shared_ptr<Util::Image> m_IndicatorBlue;

    static std::shared_ptr<Util::GameElement> m_GameElement;

    static std::vector<std::shared_ptr<Animation>> m_AnimationsLeft;
    static std::vector<std::shared_ptr<Animation>> m_AnimationsRight;
    static std::size_t                             m_LastIdxLeft;
    static std::size_t                             m_LastIdxRight;
    static bool                                    m_Flag;
};
}  // namespace Music

#endif  // FUCK_PTSD_2024_05_13_INDICATORBAR_H
