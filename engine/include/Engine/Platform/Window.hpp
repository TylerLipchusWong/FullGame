#pragma once

#include <string>

struct GLFWwindow;

namespace Engine::Platform {

class Window {
public:
    bool Create(const std::string& title, int width, int height);
    void Destroy();

    void PollEvents();
    bool ShouldClose() const;

    GLFWwindow* NativeHandle() const;
    int Width() const;
    int Height() const;

private:
    GLFWwindow* m_window {nullptr};
    int m_width {0};
    int m_height {0};
};

} // namespace Engine::Platform
