#include "App.hpp"
#include "Background.hpp"
#include "Begin.h"
#include "Character/Character.hpp"
#include "ToolBoxs.h"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "rusty_bridge/lib.h"

#include "GlobalType.h"

extern "C" {
int32_t rusty_extern_c_integer();
}

void App::Start() {
}

void App::Update() {
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
