#include "Engine/Input/InputSystem.hpp"

#include <GLFW/glfw3.h>

namespace Engine::Input {

void InputSystem::Initialize(GLFWwindow* window) {
    m_window = window;
    glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
    m_prevMouseX = m_mouseX;
    m_prevMouseY = m_mouseY;
}

void InputSystem::Shutdown() {
    m_window = nullptr;
}

void InputSystem::BeginFrame() {
    m_previousKeys = m_currentKeys;

    for (int key = 0; key < kMaxKeys; ++key) {
        m_currentKeys[key] = glfwGetKey(m_window, key) == GLFW_PRESS;
    }

    for (int button = 0; button < kMaxButtons; ++button) {
        m_mouseButtons[button] = glfwGetMouseButton(m_window, button) == GLFW_PRESS;
    }

    m_prevMouseX = m_mouseX;
    m_prevMouseY = m_mouseY;
    glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
}

bool InputSystem::IsKeyDown(int key) const {
    if (key < 0 || key >= kMaxKeys) {
        return false;
    }
    return m_currentKeys[key];
}

bool InputSystem::WasKeyPressed(int key) const {
    if (key < 0 || key >= kMaxKeys) {
        return false;
    }
    return m_currentKeys[key] && !m_previousKeys[key];
}

bool InputSystem::IsMouseButtonDown(int button) const {
    if (button < 0 || button >= kMaxButtons) {
        return false;
    }
    return m_mouseButtons[button];
}

double InputSystem::MouseDeltaX() const {
    return m_mouseX - m_prevMouseX;
}

double InputSystem::MouseDeltaY() const {
    return m_mouseY - m_prevMouseY;
}

} // namespace Engine::Input
