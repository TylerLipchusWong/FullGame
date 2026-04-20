#pragma once

#include "Engine/Math/MathTypes.hpp"

namespace Engine::Input {
class InputSystem;
}

namespace Engine::Scene {

class DebugCamera {
public:
    void Update(const Input::InputSystem& input, float deltaSeconds);

    Math::Mat4 ViewMatrix() const;
    Math::Mat4 ProjectionMatrix(float aspectRatio) const;
    Math::Vec3 Position() const;

private:
    Math::Vec3 Forward() const;

    Math::Vec3 m_position {0.0F, 1.5F, 5.0F};
    float m_pitchRadians {0.0F};
    float m_yawRadians {Math::kPi};
    float m_moveSpeed {5.0F};
    float m_lookSensitivity {0.004F};
};

} // namespace Engine::Scene
