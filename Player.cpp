#include "Player.h"
#include "Novice.h"
#include "math/Easing.h"
#include "math/M4x4.h"
#include "imgui.h"
#include <queue>

using namespace std;

const int directions[4][2] = { {-1,0},{1,0},{0,-1},{0,1} }; // 上下左右

vector<Vector2> findPathToAdjacentCell(vector<vector<int>>& grid, Vector2 start) {
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

void updateGrid(vector<vector<int>>& grid, const Vector2& oldPos, const Vector2& newPos) {
	grid[int(oldPos.x)][int(oldPos.y)] = 0; // 古い位置を空きスペースに
	grid[int(newPos.x)][int(newPos.y)] = 4; // 新しい位置にプレイヤーを設定
}

void Player::Initialize(const Vector2& position) {
	position_ = position;
}

// 方向ベクトルを計算するヘルパー関数
Vector2 Direction(const Vector2& a, const Vector2& b) {
	Vector2 dir = { b.x - a.x, b.y - a.y };
	float length = Distance(a, b);
	if (length != 0.0f) {
		dir.x /= length;
		dir.y /= length;
	}
	return dir;
}

void Player::Update(Vector2Int& mousePosition, Vector2& point, MapField& mapField) {
	// マウス位置の制限
	if (mousePosition.x > 1255) {
		mousePosition.x = 1255;
	}
	else if (mousePosition.x < 25) {
		mousePosition.x = 25;
	}
	if (mousePosition.y > 376) {
		mousePosition.y = 376;
	}
	else if (mousePosition.y < 25) {
		mousePosition.y = 25;
	}

	int PxIndex = static_cast<int>(position_.x / MapField::kBlockWidth);
	int PyIndex = static_cast<int>(position_.y / MapField::kBlockHeight);
	if (PxIndex >= 0 && PxIndex < MapField::kNumBlockHorizontal &&
		PyIndex >= 0 && PyIndex < MapField::kNumBlockVirtical) {
		mapField.mapData_[PxIndex][PyIndex] = static_cast<int>(MapType::kPlayer);
	}

	// マウスクリックで目的地を設定
	if (Novice::IsTriggerMouse(1)) {
		point = { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };

		// マップデータを更新
		int xIndex = static_cast<int>(point.x / MapField::kBlockWidth);
		int yIndex = static_cast<int>(point.y / MapField::kBlockHeight);
		if (xIndex >= 0 && xIndex < MapField::kNumBlockHorizontal &&
			yIndex >= 0 && yIndex < MapField::kNumBlockVirtical) {
			mapField.mapData_[xIndex][yIndex] = static_cast<int>(MapType::kGoal);
		}
	}

	if (position_ == point) {
		// パスを探索
		vector<Vector2> path = findPathToAdjacentCell(mapField.mapData_, position_);
		if (!path.empty()) {
			Vector2 nextPos = path[1]; // 次の移動先の位置を取得（最初の要素は現在の位置なので、次の要素を参照）

			// マップデータを更新：プレイヤーの現在位置を空白に、次の位置をプレイヤーに設定
			updateGrid(mapField.mapData_, position_, nextPos);

			// プレイヤーの位置を更新
			position_ = nextPos;
		}
	}

	// プレイヤーがポイントに到達したかどうかをチェック
	if (Distance(position_, point) <= 1.5f) {
		// ポイントに到達したら位置をポイントの位置にセットし、速度をゼロにする（停止する）
		position_ = point;
	}
	else {
		Novice::DrawEllipse(static_cast<int>(point.x), static_cast<int>(point.y), 5, 5, 0.0f, 0xff0000aa, kFillModeSolid);
	}

	// デバッグ描画
	Novice::DrawEllipse(mousePosition.x, mousePosition.y, 10, 10, 0.0f, 0x00ffff77, kFillModeSolid);
}

void Player::Draw() {
	Novice::DrawBox(static_cast<int>(position_.x), static_cast<int>(position_.y), kWidth, kHeight, 0.0f, GREEN, kFillModeSolid);
}