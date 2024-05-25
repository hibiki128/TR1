#pragma once
#include"Vector2.h"
class Player
{
private:
	static inline const int kHeight = 16;
	static inline const int kWidth = 16;
	static inline const float kMoveTime = 0.7f;

	float moveTimer_ = 0.0f;

	Vector2 position_ = {};
	Vector2 prePosition_ = {};

public:
	void Initialize(const Vector2& position);

	void Update(Vector2Int& mousePosition, Vector2& point);

	void Draw();
};

