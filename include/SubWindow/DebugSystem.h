//
// Created by adven on 2024/4/7.
//

#ifndef FUCK_PTSD_DEBUGSYSTEM_H
#define FUCK_PTSD_DEBUGSYSTEM_H
#include "Util/Root.hpp"
#include "Entity/EntityResource.h"

class DebugSystem final {
public:
    explicit DebugSystem();

    // All settings in here
    // DOTO: reset the value
    void MainWindow();
    void ResourceWindow();
    void HP();

    void ShowHelloWorld();

    void Update();

    // when apply clicked

    Resource ReturnResource();
private:
    SDL_Window* m_window;

    bool m_IsResourceWindow = false;
    bool m_IsResourceApply = false;

    // Return type
    Resource m_Resource;
};

#endif // FUCK_PTSD_DEBUGSYSTEM_H
