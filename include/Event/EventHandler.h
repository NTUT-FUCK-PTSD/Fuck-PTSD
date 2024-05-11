//
// Created by adven on 2024/5/10.
//

#ifndef FUCK_PTSD_EVENTHANDLER_H
#define FUCK_PTSD_EVENTHANDLER_H

#include <Util/Input.hpp>
#include <Util/Keycode.hpp>
#include <Util/Logger.hpp>
#include <functional>
#include <map>

namespace Events {
class EventHandler {
public:
    EventHandler() = default;

    enum class Comb { AND = 0, OR };

    //    struct TriggerCondition {
    //        std::vector<Util::Keycode> keycode;
    //        Comb                       comb;
    //    };

    struct TriggerCondition {
        Comb                  comb;
        std::function<void()> fptr;
    };

    using TC = TriggerCondition;

    void Update();

    void AddEvent(
        const std::function<void()>& fptr,
        std::vector<Util::Keycode>   code
    ) {
        m_EventList.insert({code, TC{Comb::AND, fptr}});
    };

    template <typename... Args>
    void AddEvent(const std::function<void()>& fptr, Args&&... args) {
        const std::vector<typename std::common_type<Args...>::type>&& vec = {
          args...};

        m_EventList.insert({vec, TC{Comb::OR, fptr}});
    };
    std::multimap<std::vector<Util::Keycode>, TC> m_EventList = {};
};
}  // namespace Events

#endif  // FUCK_PTSD_EVENTHANDLER_H
