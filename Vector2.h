#pragma once
class Vector2
{
public:
	float x;
	float y;

	Vector2(float x_ = 0, float y_ = 0) : x(x_), y(y_) {}

	// 加算
	Vector2 operator+(const Vector2& obj) const;
	// 減算
	Vector2 operator-(const Vector2& obj) const;
	// 乗算
	Vector2 operator*(const Vector2& obj) const;
	// 乗算(スカラー倍)
	Vector2 operator*(const float& scalar) const;
	// 除算
	Vector2 operator/(const Vector2& obj) const;
	// +=
	Vector2& operator+=(const Vector2& obj);
	// -=
	Vector2& operator-=(const Vector2& obj);
	// *=
	Vector2& operator*=(const Vector2& obj);
	// /=
	Vector2& operator/=(const Vector2& obj);
	// == 演算子の定義
	bool operator==(const Vector2& other) const;
	// != 演算子の定義
	bool operator!=(const Vector2& other) const;
};

class Vector2Int
{
public:
	int x;
	int y;

	Vector2Int(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

	// Vector2 への変換関数
	operator Vector2() const {
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}

	// 加算
	Vector2Int operator+(const Vector2Int& obj) const;
	// 減算
	Vector2Int operator-(const Vector2Int& obj) const;
	// 乗算
	Vector2Int operator*(const Vector2Int& obj) const;
	// 乗算(スカラー倍)
	Vector2Int operator*(const int& scalar) const;
	// 除算
	Vector2Int operator/(const Vector2Int& obj) const;
	// +=
	Vector2Int& operator+=(const Vector2Int& obj);
	// -=
	Vector2Int& operator-=(const Vector2Int& obj);
	// *=
	Vector2Int& operator*=(const Vector2Int& obj);
	// /=
	Vector2Int& operator/=(const Vector2Int& obj);
	// == 演算子の定義
	bool operator==(const Vector2Int& other) const;
	// != 演算子の定義
	bool operator!=(const Vector2Int& other) const;
};
