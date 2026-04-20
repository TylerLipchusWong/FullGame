#pragma once

#include <array>

struct GLFWwindow;

namespace Engine::Input {

class InputSystem {
public:
    void Initialize(GLFWwindow* window);
    void Shutdown();

    void BeginFrame();

    bool IsKeyDown(int key) const;
    bool WasKeyPressed(int key) const;
    bool IsMouseButtonDown(int button) const;

    double MouseDeltaX() const;
    double MouseDeltaY() const;

private:
    static constexpr int kMaxKeys = 349; // GLFW_KEY_LAST + 1
    static constexpr int kMaxButtons = 8; // GLFW_MOUSE_BUTTON_LAST + 1

    GLFWwindow* m_window {nullptr};
    std::array<bool, kMaxKeys> m_currentKeys {};
    std::array<bool, kMaxKeys> m_previousKeys {};
    std::array<bool, kMaxButtons> m_mouseButtons {};

    double m_mouseX {0.0};
    double m_mouseY {0.0};
    double m_prevMouseX {0.0};
    double m_prevMouseY {0.0};
};

} // namespace Engine::Input
