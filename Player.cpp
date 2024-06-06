#include "Player.h"
#include "Novice.h"
#include "math/Easing.h"
#include "math/M4x4.h"
#include "imgui.h"
#include"RouteSearch.h"

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
	if (mousePosition.x > 600) {
		mousePosition.x = 600;
	}
	else if (mousePosition.x < 40) {
		mousePosition.x = 40;
	}
	if (mousePosition.y > 600) {
		mousePosition.y = 600;
	}
	else if (mousePosition.y < 40) {
		mousePosition.y = 40;
	}

	// マウスクリックで目的地を設定
	if (Novice::IsTriggerMouse(1)) {
		point = { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };

		cooltime = 5;

		// マップデータを更新
		int xIndex = static_cast<int>(point.x / MapField::kBlockWidth);
		int yIndex = static_cast<int>(point.y / MapField::kBlockHeight);
		if (xIndex >= 0 && xIndex < MapField::kNumBlockHorizontal &&
			yIndex >= 0 && yIndex < MapField::kNumBlockVirtical) {
			// 目標地点がkBlock（1）またはkHole（2）でない場合のみ設定
			if (mapField.mapData_[xIndex][yIndex] != static_cast<int>(MapType::kBlock) &&
				mapField.mapData_[xIndex][yIndex] != static_cast<int>(MapType::kHole)) {
				mapField.mapData_[xIndex][yIndex] = static_cast<int>(MapType::kGoal);
			}
		}
	}

	if (cooltime > 0) {
		cooltime -= 1;
	}

	if (cooltime <= 0) {
		// パスを探索
		std::vector<Vector2> path = RouteSearch::findPathToAdjacentCell(mapField.mapData_, position_);
		if (!path.empty()) {
			Vector2 nextPos = path[1]; // 次の移動先の位置を取得（最初の要素は現在の位置なので、次の要素を参照）

			// マップデータを更新：プレイヤーの現在位置を空白に、次の位置をプレイヤーに設定
			RouteSearch::updateGrid(mapField.mapData_, position_, nextPos);

			// プレイヤーの位置を更新
			position_ = nextPos;
		}
		cooltime = 5;
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

void Player::Draw(MapField& mapField) {
	//Novice::DrawBox(static_cast<int>(position_.x), static_cast<int>(position_.y), kWidth, kHeight, 0.0f, GREEN, kFillModeSolid);
	for (uint32_t y = 0; y < mapField.kNumBlockVirtical; ++y) {
		for (uint32_t x = 0; x < mapField.kNumBlockHorizontal; ++x) {
			MapType type = mapField.GetMapChipTypeByIndex(x, y);
			Vector2 position = mapField.GetMapChipPositionByIndex(x, y);
			int width = static_cast<int>(mapField.kBlockWidth);
			int height = static_cast<int>(mapField.kBlockWidth);

			if (type == MapType::kPlayer) {
				// 障害物の描画
				Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, GREEN, kFillModeSolid);
			}
		}
	}
}