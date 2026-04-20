#include "Engine/Scene/DebugCamera.hpp"

#include "Engine/Input/InputSystem.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>

namespace Engine::Scene {

void DebugCamera::Update(const Input::InputSystem& input, float deltaSeconds) {
    m_yawRadians -= static_cast<float>(input.MouseDeltaX()) * m_lookSensitivity;
    m_pitchRadians -= static_cast<float>(input.MouseDeltaY()) * m_lookSensitivity;
    m_pitchRadians = std::clamp(m_pitchRadians, -1.4F, 1.4F);

    const Math::Vec3 forward = Forward();
    const Math::Vec3 right = Math::Normalize(Math::Cross(forward, {0.0F, 1.0F, 0.0F}));

    Math::Vec3 move {};
    if (input.IsKeyDown(GLFW_KEY_W)) {
        move += forward;
    }
    if (input.IsKeyDown(GLFW_KEY_S)) {
        move += forward * -1.0F;
    }
    if (input.IsKeyDown(GLFW_KEY_D)) {
        move += right;
    }
    if (input.IsKeyDown(GLFW_KEY_A)) {
        move += right * -1.0F;
    }
    if (input.IsKeyDown(GLFW_KEY_E)) {
        move.y += 1.0F;
    }
    if (input.IsKeyDown(GLFW_KEY_Q)) {
        move.y -= 1.0F;
    }

    const Math::Vec3 normalizedMove = Math::Normalize(move);
    m_position += normalizedMove * (m_moveSpeed * deltaSeconds);
}

Math::Mat4 DebugCamera::ViewMatrix() const {
    return Math::LookAt(m_position, m_position + Forward(), {0.0F, 1.0F, 0.0F});
}

Math::Mat4 DebugCamera::ProjectionMatrix(float aspectRatio) const {
    return Math::Perspective(60.0F * (Math::kPi / 180.0F), aspectRatio, 0.1F, 500.0F);
}

Math::Vec3 DebugCamera::Position() const {
    return m_position;
}

Math::Vec3 DebugCamera::Forward() const {
    const float cp = std::cos(m_pitchRadians);
    return Math::Normalize({
        std::sin(m_yawRadians) * cp,
        std::sin(m_pitchRadians),
        std::cos(m_yawRadians) * cp
    });
}

} // namespace Engine::Scene
