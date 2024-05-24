#include "MyGame.h"
#include"Novice.h"
#include"imgui.h"

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
	delete mapChipField_;
}

void MyGame::Initialize()
{
	mapChipField_ = new MapChipField();
	mapChipField_->GenerateRandomObstacles(blockNum2x2, blockNum3x3, holeNum3x2, holeNum4x3);
}

void MyGame::Update()
{
	ImGui::Begin(" ");
	ImGui::SliderInt("2x2Block", &blockNum2x2, 0, 10);  // 最小値0、最大値10
	ImGui::SliderInt("3x3Block", &blockNum3x3, 0, 10);  // 最小値0、最大値10
	ImGui::SliderInt("3x2Hole", &holeNum3x2, 0, 10);    // 最小値0、最大値10
	ImGui::SliderInt("4x3Hole", &holeNum4x3, 0, 10);    // 最小値0、最大値10

	// ボタンの作成とクリック時の処理
	if (ImGui::Button("Generate Random Obstacles")) {
		mapChipField_->GenerateRandomObstacles(blockNum2x2, blockNum3x3, holeNum3x2, holeNum4x3);
	}
	ImGui::End();
}

void MyGame::Draw() {
	// 全てのマップチップを描画
	for (uint32_t y = 0; y < mapChipField_->GetNumBlockVirtical(); ++y) {
		for (uint32_t x = 0; x < mapChipField_->GetNumBlockHorizontal(); ++x) {
			MapChipType type = mapChipField_->GetMapChipTypeByIndex(x, y);
			Vector3 position = mapChipField_->GetMapChipPositionByIndex(x, y);
			int width = static_cast<int>(mapChipField_->GetBlockWidth());
			int height = static_cast<int>(mapChipField_->GetBlockHeight());

			if (type == MapChipType::kBlock) {
				// 障害物の描画
				Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, RED, kFillModeSolid);
			}
			else if (type == MapChipType::kBorder) {
				// 枠の描画
				Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, WHITE, kFillModeWireFrame);
			}
			else if (type == MapChipType::kHole) {
				// 穴の描画
				Novice::DrawBox(static_cast<int>(position.x), static_cast<int>(position.y), width, height, 0.0f, BLACK, kFillModeSolid);
			}
		}
	}
}

void MyGame::GenerateBlocks()
{

}
