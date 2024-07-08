#pragma once
#include"vector"
#include"Vector2.h"

class RouteSearch
{
private:

	static inline const int directions[4][2] = { {-1,0},{1,0},{0,-1},{0,1} }; // 上下左右

public:
	static std::vector<Vector2> findPathToAdjacentCell(std::vector < std::vector<int >>& grid, Vector2 start, int goalNum);
	static void updateGrid(std::vector<std::vector<int>>& grid, const Vector2& oldPos, const Vector2& newPos, int playerNum);
};

