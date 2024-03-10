//
// Created by adven on 2024/3/10.
//

#ifndef FUCK_PTSD_EVENT_H
#define FUCK_PTSD_EVENT_H

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

namespace Event {
bool isKeyDown_W() {
    return Util::Input::IsKeyDown(Util::Keycode::W);
}
} // namespace Event

#endif // FUCK_PTSD_EVENT_H
