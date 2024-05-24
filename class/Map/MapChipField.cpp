#include "MapChipField.h"
#include "cassert"
#include "random"
#include "vector"
#include <iostream>

void MapChipField::GenerateRandomObstacles(int blockNum2x2, int blockNum3x3, int holeNum3x2, int holeNum4x3) {
    // マップの初期化
    ResetMapChipData();

    // マップのサイズに基づいてブロックの数を計算する
    const int kBlockHorizontal = kNumBlockHorizontal;
    const int kBlockVertical = kNumBlockVirtical;

    for (auto& row : mapChipData_.data) {
        std::fill(row.begin(), row.end(), MapChipType::kBlank);
    }

    // 周囲に枠を追加する
    for (int x = 0; x < kBlockHorizontal; ++x) {
        mapChipData_.data[0][x] = MapChipType::kBorder;
        mapChipData_.data[kBlockVertical - 1][x] = MapChipType::kBorder;
    }
    for (int y = 0; y < kBlockVertical; ++y) {
        mapChipData_.data[y][0] = MapChipType::kBorder;
        mapChipData_.data[y][kBlockHorizontal - 1] = MapChipType::kBorder;
    }

    std::random_device rd;
    std::mt19937 rng(rd());

    auto placeObject = [&](int width, int height, MapChipType type) {
        bool placed = false;
        while (!placed) {
            int x = rng() % (kBlockHorizontal - width);
            int y = rng() % (kBlockVertical - height);

            // オブジェクトを配置可能かどうかをチェックする
            bool canPlace = true;
            if (x + width <= kBlockHorizontal && y + height <= kBlockVertical) {
                for (int i = 0; i < width; ++i) {
                    for (int j = 0; j < height; ++j) {
                        if (mapChipData_.data[y + j][x + i] != MapChipType::kBlank) {
                            canPlace = false;
                            break;
                        }
                    }
                    if (!canPlace) break;
                }
            }
            else {
                canPlace = false;
            }

            if (canPlace) {
                for (int i = 0; i < width; ++i) {
                    for (int j = 0; j < height; ++j) {
                        mapChipData_.data[y + j][x + i] = type;
                    }
                }
                placed = true;
            }
        }
        };

    // 指定された数の2x2の障害物を配置する
    for (int i = 0; i < blockNum2x2; ++i) {
        placeObject(2, 2, MapChipType::kBlock);
    }

    // 指定された数の3x3の障害物を配置する
    for (int i = 0; i < blockNum3x3; ++i) {
        placeObject(3, 3, MapChipType::kBlock);
    }

    // 指定された数の3x2の穴を配置する
    for (int i = 0; i < holeNum3x2; ++i) {
        placeObject(3, 2, MapChipType::kHole);
    }

    // 指定された数の4x3の穴を配置する
    for (int i = 0; i < holeNum4x3; ++i) {
        placeObject(4, 3, MapChipType::kHole);
    }
}

void MapChipField::ResetMapChipData() {
	// マップチップデータをリセット
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumBlockVirtical - 1 < yIndex) {
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) {
	return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVirtical - 1 - yIndex), 0);
}

IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position) {
	IndexSet indexSet = {};

	// x座標から水平インデックスを計算
	indexSet.xIndex = uint32_t((position.x + kBlockWidth / 2) / kBlockWidth);

	// y座標から垂直インデックスを計算
	indexSet.yIndex = kNumBlockVirtical - 1 - uint32_t((position.y + kBlockHeight / 2) / kBlockHeight);

	return indexSet;
}

MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
	// 指定ブロックの中心座標を取得する
	Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);

	Rect rect;

	// 中心座標から矩形の範囲を計算
	rect.left = center.x - kBlockWidth / 2.0f;
	rect.right = center.x + kBlockWidth / 2.0f;
	rect.bottom = center.y - kBlockHeight / 2.0f;
	rect.top = center.y + kBlockHeight / 2.0f;

	return rect;
}

