#pragma once

#include <cmath>

struct Vector3 {
public:
	float x, y, z;

	constexpr Vector3(const float x = 0.f, const  float y = 0.f, const  float z = 0.f) : x(x), y(y), z(z) {};
	
	constexpr const Vector3& operator+(const Vector3& vec) const {
		return Vector3{ vec.x + x, vec.y + y, vec.z + z };
	}

	constexpr const Vector3& operator-(const Vector3& vec) {
		return Vector3{ x - vec.x, y - vec.y, z - vec.z };
	}

	constexpr const Vector3& operator*(const Vector3& vec) {
		return Vector3{ vec.x * x, vec.y * y, vec.z * z };

	}

	constexpr const Vector3& operator/(const Vector3 & vec) {
		return Vector3{vec.x / x, vec.y / y, vec.z / z};
	}
};