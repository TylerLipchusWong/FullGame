#include "Engine/Platform/Window.hpp"

#include "Engine/Core/Logger.hpp"

#include <GLFW/glfw3.h>

namespace Engine::Platform {

bool Window::Create(const std::string& title, int width, int height) {
    if (!glfwInit()) {
        Core::Logger::Log(Core::LogLevel::Error, "Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (m_window == nullptr) {
        Core::Logger::Log(Core::LogLevel::Error, "Failed to create GLFW window");
        glfwTerminate();
        return false;
    }

    m_width = width;
    m_height = height;
    return true;
}

void Window::Destroy() {
    if (m_window != nullptr) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

void Window::PollEvents() {
    glfwPollEvents();
}

bool Window::ShouldClose() const {
    return m_window == nullptr || glfwWindowShouldClose(m_window) != 0;
}

GLFWwindow* Window::NativeHandle() const {
    return m_window;
}

int Window::Width() const {
    return m_width;
}

int Window::Height() const {
    return m_height;
}

} // namespace Engine::Platform
