#pragma once
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 100.0f

struct Vector2
{
	float x, y;

	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

	float MagnitudeSquared() {
		return x * x + y * y;
	}

	float Magnitude() {
		return (float)sqrt(MagnitudeSquared());
	}

	Vector2 Normalized() {
		float mag = Magnitude();

		return Vector2(x / mag, y / mag);
	}

	Vector2& operator +=(const Vector2& right)
	{
		x += right.x;
		y += right.y;

		return *this;
	}

	Vector2& operator -=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;

		return *this;
	}
};

inline Vector2 operator +(const Vector2& left, const Vector2& right)
{
	return Vector2(left.x + right.x, left.y + right.y);
}

inline Vector2 operator +(const Vector2& left, const float& right)
{
	return Vector2(left.x + right, left.y + right);
}

inline Vector2 operator -(const Vector2& left, const Vector2& right)
{
	return Vector2(left.x - right.x, left.y - right.y);
}

inline Vector2 operator *(const Vector2& left, const float right)
{
	return Vector2(left.x * right, left.y * right);
}

inline Vector2 operator * (const float& left, const Vector2& right)
{
	return Vector2(left * right.x, left * right.y);
}

inline Vector2 operator /(const Vector2& left, const float right)
{
	return Vector2(left.x / right, left.y / right);
}

inline Vector2 operator / (const float& left, const Vector2& right)
{
	return Vector2(left / right.x, left / right.y);
}

inline Vector2 RotateVector(Vector2& vec, float angle)
{
	float radAngle = (float)(angle * DEG_TO_RAD);

	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

const Vector2 VEC2_ZERO = { 0.0f,0.0f };
const Vector2 VEC2_ONE = { 1.0f,1.0f };
const Vector2 VEC2_UP = { 0.0f,1.0f };
const Vector2 VEC2_RIGHT = { 1.0f,0.0f };
