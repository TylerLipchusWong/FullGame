#include "Engine/Math/MathTypes.hpp"

#include <cmath>

namespace Engine::Math {

Vec3 Vec3::operator+(const Vec3& rhs) const {
    return {x + rhs.x, y + rhs.y, z + rhs.z};
}

Vec3 Vec3::operator-(const Vec3& rhs) const {
    return {x - rhs.x, y - rhs.y, z - rhs.z};
}

Vec3 Vec3::operator*(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

Vec3& Vec3::operator+=(const Vec3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Mat4 Mat4::Identity() {
    Mat4 result {};
    result.m = {
        1.0F, 0.0F, 0.0F, 0.0F,
        0.0F, 1.0F, 0.0F, 0.0F,
        0.0F, 0.0F, 1.0F, 0.0F,
        0.0F, 0.0F, 0.0F, 1.0F
    };
    return result;
}

float Dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Cross(const Vec3& a, const Vec3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

float Length(const Vec3& value) {
    return std::sqrt(Dot(value, value));
}

Vec3 Normalize(const Vec3& value) {
    const float len = Length(value);
    if (len <= 0.000001F) {
        return {};
    }
    return value * (1.0F / len);
}

Mat4 Perspective(float fovRadians, float aspect, float nearPlane, float farPlane) {
    const float tanHalfFov = std::tan(fovRadians * 0.5F);

    Mat4 result {};
    result.m = {
        1.0F / (aspect * tanHalfFov), 0.0F, 0.0F, 0.0F,
        0.0F, 1.0F / tanHalfFov, 0.0F, 0.0F,
        0.0F, 0.0F, farPlane / (nearPlane - farPlane), -1.0F,
        0.0F, 0.0F, (nearPlane * farPlane) / (nearPlane - farPlane), 0.0F
    };
    return result;
}

Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
    const Vec3 forward = Normalize(target - eye);
    const Vec3 right = Normalize(Cross(forward, up));
    const Vec3 trueUp = Cross(right, forward);

    Mat4 result {};
    result.m = {
        right.x, trueUp.x, -forward.x, 0.0F,
        right.y, trueUp.y, -forward.y, 0.0F,
        right.z, trueUp.z, -forward.z, 0.0F,
        -Dot(right, eye), -Dot(trueUp, eye), Dot(forward, eye), 1.0F
    };
    return result;
}

} // namespace Engine::Math
