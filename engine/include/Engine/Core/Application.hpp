#pragma once

#include "Engine/Input/InputSystem.hpp"
#include "Engine/Platform/Window.hpp"
#include "Engine/Render/VulkanRenderer.hpp"
#include "Engine/Scene/DebugCamera.hpp"

#include <chrono>

namespace Engine::Core {

class Application {
public:
    bool Initialize();
    int Run();
    void Shutdown();

private:
    Platform::Window m_window;
    Input::InputSystem m_input;
    Render::VulkanRenderer m_renderer;
    Scene::DebugCamera m_camera;

    std::chrono::steady_clock::time_point m_lastFrameTime;
};

} // namespace Engine::Core
