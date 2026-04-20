#pragma once

#include <array>

namespace Engine::Math {

constexpr float kPi = 3.14159265359F;

struct Vec3 {
    float x {0.0F};
    float y {0.0F};
    float z {0.0F};

    Vec3 operator+(const Vec3& rhs) const;
    Vec3 operator-(const Vec3& rhs) const;
    Vec3 operator*(float scalar) const;

    Vec3& operator+=(const Vec3& rhs);
};

struct Mat4 {
    std::array<float, 16> m {};

    static Mat4 Identity();
};

float Dot(const Vec3& a, const Vec3& b);
Vec3 Cross(const Vec3& a, const Vec3& b);
float Length(const Vec3& value);
Vec3 Normalize(const Vec3& value);

Mat4 Perspective(float fovRadians, float aspect, float nearPlane, float farPlane);
Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up);

} // namespace Engine::Math
