//
// Created by 陳世昂 on 2024/5/11.
//

#include "Event/EventHandler.h"

static auto JudgeANDFunc = [](const std::vector<Util::Keycode>& keycode) {
    for (auto i : keycode) {
        if (!Util::Input::IsKeyDown(i)) {
            return false;
        }
    }
    return true;
};

static auto JudgeORFunc = [](const std::vector<Util::Keycode>& keycode) {
    for (auto i : keycode) {
        if (Util::Input::IsKeyDown(i)) {
            return true;
        }
    }
    return false;
};

namespace Events {
void EventHandler::Update() {
    std::for_each(m_EventList.begin(), m_EventList.end(), [](const auto& elem) {
        bool condition = false;

        // not comba
        if (elem.first.size() == 1 && Util::Input::IsKeyDown(elem.first[0])) {
            elem.second.fptr();
        } else if (elem.second.comb == Comb::OR) {
            condition = JudgeORFunc(elem.first);
        } else if (elem.second.comb == Comb::AND) {
            condition = JudgeANDFunc(elem.first);
        }

        if (condition) {
            elem.second.fptr();
        }
    });
}
}  // namespace Events
