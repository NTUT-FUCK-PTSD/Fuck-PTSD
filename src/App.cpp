#include "App.hpp"

#include "Display/BeatIndicator.h"
#include "Music/Tempo.h"

App::App() {
    Window::Init();
    m_DeadScreen = std::make_shared<Settings::DeadScreen>();
    m_DeadScreen->SetPosition({0, -200});
    m_DeadScreen->SetVisibleRecursive(false);
    m_Camera->AddUIChild(m_DeadScreen);
};

void App::SetDeadScreen(const bool deadScreenVisible) {
    m_MainCharacter->SetVisible(!deadScreenVisible);
    m_DeadScreen->SetVisibleRecursive(deadScreenVisible);
    Music::Tempo::Pause(deadScreenVisible);
    Display::BeatIndicator::Pause(deadScreenVisible);
}
