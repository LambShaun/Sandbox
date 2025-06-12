/**
 * @file	Vec2D.h
 * @brief	2维向量数学模板
 * @author	LambShaun
 **/

#pragma once

#include "Math.h"

namespace Luxon {
namespace Core {
namespace Math {
	template<typename T>
	struct Vector2 {
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);

		Vector2() = default;
		Vector2(T x_val, T y_val) :x(x_val), y(y_val) {}

		T LengthSquared() const {
			return x * x + y * y;
		}

		// 计算向量模(长度)
		T Length() const {
			return static_cast<T>(Math::Sqrt(LengthSquared()));
		}

		// 将当前向量归一化(单位向量)
		void Normalize() {
			const T length = Length();
			if (length != static_cast<T>(0)) {
				x /= length;
				y /= length;
			}
		}

		// 返回归一化后的新向量
		Vector2<T> Normalized() const {
			Vector2<T> result = *this;
			result.Normalize();
			return result;
		}

		Vector2<T> operator+(const Vector2<T>& other) const {
			return Vector2<T>(x + other.x, y + other.y);
		}

		Vector2<T>& operator+=(const Vector2<T>& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2<T> operator-(const Vector2<T>& other) const {
			return Vector2<T>(x - other.x, y - other.y);
		}

		Vector2<T>& operator-=(const Vector2<T>& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2<T> operator*(T scalar) const {
			return Vector2<T>(x * scalar, y * scalar);
		}

		Vector2<T>& operator*=(T scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vector2<T> operator/(T scalar) const {
			if (scalar == static_cast<T>(0)) return Vector2<T>();
			return Vector2<T>(x / scalar, y / scalar);
		}

		Vector2<T>& operator/=(T scalar) {
			if (scalar != static_cast<T>(0)) {
				x /= scalar;
				y /= scalar;
			}
			return *this;
		}

		Vector2<T> operator-() const {
			return Vector2<T>(-x, -y);
		}

		bool operator==(const Vector2<T>& other) const {
			return  x == other.x && y == other.y;
		}

		bool operator!=(const Vector2<T>& other) const {
			return !(*this == other);
		}
	};

	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2d = Vector2<double>;

} // namespace Math
} // namespace Core
} // namespace Luxon