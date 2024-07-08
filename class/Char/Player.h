#pragma once
#include"class/Map/MapField.h"
class Player
{
private:
	static inline const int kHeight = 16;
	static inline const int kWidth = 16;

	Vector2 position_;
	float cooltime = 0;


public:
	void Initialize(const Vector2& position);

	void Update(Vector2Int& mousePosition, Vector2& point, MapField& mapField);

	void Draw(MapField& mapField);
};
