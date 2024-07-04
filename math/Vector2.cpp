#include "Vector2.h"

// 加算
Vector2 Vector2::operator+(const Vector2& obj) const { return Vector2(x + obj.x, y + obj.y); }

// 減算
Vector2 Vector2::operator-(const Vector2& obj) const { return Vector2(x - obj.x, y - obj.y); }

// 乗算
Vector2 Vector2::operator*(const Vector2& obj) const { return Vector2(x * obj.x, y * obj.y); }

// 乗算(スカラー倍)
Vector2 Vector2::operator*(const float& scalar) const { return Vector2(x * scalar, y * scalar); }

// 除算
Vector2 Vector2::operator/(const Vector2& obj) const { return Vector2(x / obj.x, y / obj.y); }

// +=
Vector2& Vector2::operator+=(const Vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

// -=
Vector2& Vector2::operator-=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

// *=
Vector2& Vector2::operator*=(const Vector2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

// /=
Vector2& Vector2::operator/=(const Vector2& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}
// == 演算子の定義
bool Vector2::operator==(const Vector2& other) const {
	return (x == other.x) && (y == other.y);
}

// != 演算子の定義
bool Vector2::operator!=(const Vector2& other) const {
	return !(*this == other);
}


// 加算
Vector2Int Vector2Int::operator+(const Vector2Int& obj) const { return Vector2Int(x + obj.x, y + obj.y); }

// 減算
Vector2Int Vector2Int::operator-(const Vector2Int& obj) const { return Vector2Int(x - obj.x, y - obj.y); }

// 乗算
Vector2Int Vector2Int::operator*(const Vector2Int& obj) const { return Vector2Int(x * obj.x, y * obj.y); }

// 乗算(スカラー倍)
Vector2Int Vector2Int::operator*(const int& scalar) const { return Vector2Int(x * scalar, y * scalar); }

// 除算
Vector2Int Vector2Int::operator/(const Vector2Int& obj) const { return Vector2Int(x / obj.x, y / obj.y); }

// +=
Vector2Int& Vector2Int::operator+=(const Vector2Int& other) {
	x += other.x;
	y += other.y;
	return *this;
}

// -=
Vector2Int& Vector2Int::operator-=(const Vector2Int& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

// *=
Vector2Int& Vector2Int::operator*=(const Vector2Int& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

// /=
Vector2Int& Vector2Int::operator/=(const Vector2Int& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

// == 演算子の定義
bool Vector2Int::operator==(const Vector2Int& other) const {
	return (x == other.x) && (y == other.y);
}

// != 演算子の定義
bool Vector2Int::operator!=(const Vector2Int& other) const {
	return !(*this == other);
}
