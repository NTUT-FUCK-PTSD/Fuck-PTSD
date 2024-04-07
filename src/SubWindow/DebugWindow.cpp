//
// Created by adven on 2024/4/7.
//
#include "SubWindow/DebugSystem.h"
#include "Util/Logger.hpp"
#include "Util/Root.hpp"
#include "Util/Time.hpp"
#include <iostream>

DebugSystem::DebugSystem()
    : m_Resource(false, 0, 0, 0, 0, 0.0f, 0.0f){};

void DebugSystem::Update() {
    this->MainWindow();

    // show resource window. default: false
    if (m_IsResourceWindow) {
        this->ResourceWindow();
    }
}

void DebugSystem::MainWindow() {
    ImGui::Begin("Settings Penal");
    ImGui::Text("This is the panel for debug");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                Util::Time::GetDeltaTime() * 1000.0f,
                1.0f / Util::Time::GetDeltaTime());
    ImGui::Checkbox("Resource Window", &m_IsResourceWindow);
    ImGui::End();
}

void DebugSystem::ResourceWindow() {
    ImGui::Begin("Resource Window");
    ImGui::Text("This window can modify the resource");
    //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
    //    Util::Time::GetDeltaTime() * 1000.0f, 1.0f /
    //    Util::Time::GetDeltaTime());
    ImGui::End();
}

void DebugSystem::ShowHelloWorld() {
    ImGui::Begin("Giraffe Text");
    ImGui::SetWindowSize({300, 100});
    ImGui::Text("Hello, world %d", 123);
    ImGui::End();
}

void DebugSystem::HP() {}

Resource DebugSystem::ReturnResource() {
    if (!m_IsResourceApply) {
        return Resource{false, 0, 0, 0, 0, 0.0f, 0.0f};
    }

    auto copy = m_Resource;
    return copy;
}
