//
// Created by adven on 2024/5/10.
//

#include "App.hpp"

struct ClickEventType {
    std::vector<Util::Keycode> code;
    std::function<void()>      fptr;
};

using CET = ClickEventType;

auto printT = ClickEventType{{Util::Keycode::T}, []() { LOG_INFO("T"); }};

auto test2 = CET{{Util::Keycode::RIGHT, Util::Keycode::LEFT}, []() {
                     LOG_INFO("cond");
                 }};

void App::BeforeUpdate() {
    m_EventHandler.AddEvent(printT.code, printT.fptr);
    m_EventHandler.AddEvent(test2.code, test2.fptr);
};
