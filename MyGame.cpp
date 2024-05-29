#include "MyGame.h"
#include "Novice.h"
#include "imgui.h"

MyGame::MyGame() {
}

MyGame::~MyGame() {
	delete mapField_;
	delete player_;
}

void MyGame::Initialize() {
	mapField_ = new MapField();
	mapField_->GenerateRandomObstacles(blockNum2x2, blockNum3x3, holeNum3x2, holeNum4x3);

	player_ = new Player();
	player_->Initialize({16,16});
}

void MyGame::Update() {
	ImGui::Begin(" ");
	ImGui::SliderInt("2x2Block", &blockNum2x2, 0, 10);  // 最小値0、最大値10
	ImGui::SliderInt("3x3Block", &blockNum3x3, 0, 10);  // 最小値0、最大値10
	ImGui::SliderInt("3x2Hole", &holeNum3x2, 0, 10);    // 最小値0、最大値10
	ImGui::SliderInt("4x3Hole", &holeNum4x3, 0, 10);    // 最小値0、最大値10

	// ボタンの作成とクリック時の処理
	if (ImGui::Button("Generate Random Obstacles")) {
		mapField_->GenerateRandomObstacles(blockNum2x2, blockNum3x3, holeNum3x2, holeNum4x3);
	}
	ImGui::End();

	Novice::GetMousePosition(&mousePosition_.x, &mousePosition_.y);
	player_->Update(mousePosition_, point, *mapField_);
}

void MyGame::Draw() {
    bool goalDrawn = false; // kGoalが既に描画されたかどうかのフラグ

    // 全てのマップチップを描画
    for (uint32_t y = 0; y < mapField_->kNumBlockVirtical; ++y) {
        for (uint32_t x = 0; x < mapField_->kNumBlockHorizontal; ++x) {
            MapType type = mapField_->GetMapChipTypeByIndex(x, y);
            Vector2 position = mapField_->GetMapChipPositionByIndex(x, y);
            int width = static_cast<int>(mapField_->kBlockWidth);
            int height = static_cast<int>(mapField_->kBlockWidth);

            if (type == MapType::kBlock) {
                // 障害物の描画
                Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, RED, kFillModeSolid);
                Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, WHITE, kFillModeWireFrame);
            }
            else if (type == MapType::kBorder) {
                // 枠の描画
                Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, WHITE, kFillModeWireFrame);
            }
            else if (type == MapType::kHole) {
                // 穴の描画
                Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, BLACK, kFillModeSolid);
                Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, WHITE, kFillModeWireFrame);
            }
            else if (type == MapType::kGoal && !goalDrawn) {
                // kGoalの描画（最初に見つかった場所のみ描画）
                Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, 0xffff00aa, kFillModeSolid);
                Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, WHITE, kFillModeWireFrame);
                goalDrawn = true; // フラグをセット
            }
        }
    }

    player_->Draw();
}