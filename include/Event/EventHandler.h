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

    void Update() {
        std::for_each(
            m_ListenEvent.begin(),
            m_ListenEvent.end(),
            [](const auto& elem) {
                if (elem.first.size() == 1
                    && Util::Input::IsKeyDown(elem.first[0])) {
                    elem.second();
                } else {
                    bool cond = true;
                    for (std::size_t i = 0; i < elem.first.size(); i++) {
                        if (!Util::Input::IsKeyDown(elem.first[i])) {
                            cond = false;
                        }
                    }

                    if (cond) {
                        elem.second();
                    }
                }
            }
        );

        std::for_each(
            m_ListenEventOr.begin(),
            m_ListenEventOr.end(),
            [](const auto& elem) {
                if (elem.first.size() == 1
                    && Util::Input::IsKeyDown(elem.first[0])) {
                    elem.second();
                } else {
                    bool cond = false;
                    for (std::size_t i = 0; i < elem.first.size(); i++) {
                        if (Util::Input::IsKeyDown(elem.first[i])) {
                            cond = true;
                        }
                    }

                    if (cond) {
                        elem.second();
                    }
                }
            }
        );
    }

    void AddEvent(
        const std::function<void()>& fptr,
        std::vector<Util::Keycode>   code
    ) {
        m_ListenEvent.insert({code, fptr});
    };

    template <typename... Args>
    void AddEvent(const std::function<void()>& fptr, Args&&... args) {
        const std::vector<typename std::common_type<Args...>::type>&& vec = {
          args...};

        m_ListenEventOr.insert({vec, fptr});

        //        std::for_each(
        //            m_ListenEventOr.begin(),
        //            m_ListenEventOr.end(),
        //            [](const auto& e) {
        //                auto a = e.first;
        //                auto b = e.second;
        //            }
        //        );
    };

    std::map<std::vector<Util::Keycode>, std::function<void()>> m_ListenEvent =
        {};

    std::multimap<std::vector<Util::Keycode>, std::function<void()>>
        m_ListenEventOr = {};
    //        {{{Util::Keycode::T}, []() { LOG_DEBUG("T"); }}};
};
}  // namespace Events

#endif  // FUCK_PTSD_EVENTHANDLER_H
