//
// Created by adven on 2024/3/2.
//

#include "ToolBoxs.h"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

bool ToolBoxs::IsAnyKeyPress() {
    for (int i = 0; i < 512; i++) {
        if (Util::Input::IsKeyPressed((Util::Keycode)i)) {
            return true;
        }
    }
    return false;
}