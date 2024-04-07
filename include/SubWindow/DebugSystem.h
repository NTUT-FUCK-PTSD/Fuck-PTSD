//
// Created by adven on 2024/4/7.
//

#ifndef FUCK_PTSD_DEBUGSYSTEM_H
#define FUCK_PTSD_DEBUGSYSTEM_H
#include "Util/Root.hpp"

class DebugSystem final {
public:
    explicit DebugSystem();

    void MainWindow();

    void ResourceWindow();

    void ShowHelloWorld();
    void HP();

    void Update();
private:
    SDL_Window* m_window;

    bool m_IsResourceWindow = false;
};

#endif // FUCK_PTSD_DEBUGSYSTEM_H
