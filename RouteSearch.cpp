#include "RouteSearch.h"
#include"class/Map/MapField.h"
#include <queue>

using namespace std;

vector<Vector2> RouteSearch::findPathToAdjacentCell(vector<vector<int>>& grid, Vector2 start) {
	int rows = MapField::kNumBlockHorizontal;
	int cols = MapField::kNumBlockVirtical;
	vector<vector<bool>> visited(rows, vector<bool>(cols, false));
	vector<vector<Vector2>> previous(rows, vector<Vector2>(cols, { -1, -1 })); // 経路追跡用
	queue<Vector2> q;

	q.push(start);
	visited[int(start.x)][int(start.y)] = true;

	while (!q.empty()) {
		Vector2 current = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nx = int(current.x) + directions[i][0];
			int ny = int(current.y) + directions[i][1];

			if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny]) {
				visited[nx][ny] = true;
				previous[nx][ny] = current;

				if (grid[nx][ny] == 5) { // 5が敵を表す
					// 敵の隣接セルまでの経路を復元
					vector<Vector2> path;
					Vector2 step = { float(nx), float(ny) };
					while (step != start) {
						path.push_back(step);
						step = previous[int(step.x)][int(step.y)];
					}
					path.push_back(start);
					reverse(path.begin(), path.end());
					return path;
				}

				if (grid[nx][ny] == 0) { // 0が空きスペースを表す
					q.push(Vector2{ float(nx), float(ny) });
				}
			}
		}
	}

	return {}; // 敵が見つからなかった場合
}

void RouteSearch::updateGrid(vector<vector<int>>& grid, const Vector2& oldPos, const Vector2& newPos)
{
	grid[int(oldPos.x)][int(oldPos.y)] = 0; // 古い位置を空きスペースに
	grid[int(newPos.x)][int(newPos.y)] = 4; // 新しい位置にプレイヤーを設定
}