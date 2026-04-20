#include "Engine/Core/Application.hpp"

#include "Engine/Core/Logger.hpp"

#include <GLFW/glfw3.h>

namespace Engine::Core {

bool Application::Initialize() {
    Logger::Initialize();

    if (!m_window.Create("ThirdPersonSandbox - Phase 1", 1600, 900)) {
        Logger::Log(LogLevel::Error, "Window initialization failed");
        Shutdown();
        return false;
    }

    m_input.Initialize(m_window.NativeHandle());

    if (!m_renderer.Initialize(m_window.NativeHandle(), m_window.Width(), m_window.Height())) {
        Logger::Log(LogLevel::Error, "Renderer initialization failed");
        Shutdown();
        return false;
    }

    glfwSetInputMode(m_window.NativeHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_lastFrameTime = std::chrono::steady_clock::now();
    Logger::Log(LogLevel::Info, "Application initialized");
    return true;
}

int Application::Run() {
    while (!m_window.ShouldClose()) {
        m_window.PollEvents();
        m_input.BeginFrame();

        if (m_input.WasKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(m_window.NativeHandle(), GLFW_TRUE);
        }

        const auto now = std::chrono::steady_clock::now();
        const auto dt = std::chrono::duration<float>(now - m_lastFrameTime);
        m_lastFrameTime = now;

        m_camera.Update(m_input, dt.count());

        if (!m_renderer.BeginFrame()) {
            Logger::Log(LogLevel::Error, "BeginFrame failed");
            return 1;
        }

        if (!m_renderer.EndFrame()) {
            Logger::Log(LogLevel::Error, "EndFrame failed");
            return 1;
        }
    }

    return 0;
}

void Application::Shutdown() {
    m_renderer.Shutdown();
    m_input.Shutdown();
    m_window.Destroy();
    Logger::Shutdown();
}

} // namespace Engine::Core
