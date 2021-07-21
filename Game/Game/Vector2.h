#pragma once

//Vector2
struct Vector2
{
	int x;
	int y;

	//コンストラクタ
	Vector2() = default;
	constexpr Vector2(int xy) :x(xy), y(xy) {}
	constexpr Vector2(int _x, int _y) : x(_x), y(_y) {}

	Vector2 operator +(const Vector2& vec) const {
		return{ x + vec.x, y + vec.y };
	}
	Vector2 operator -(const Vector2& vec) const {
		return{ x - vec.x, y - vec.y };
	}
	Vector2 operator /(const Vector2& vec) const {
		return{ x / vec.x, y / vec.y };
	}
	Vector2 operator *(const Vector2& vec) const {
		return{ x * vec.x, y * vec.y };
	}
};