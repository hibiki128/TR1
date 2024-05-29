// MapField.h

#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Vector2.h"
#include <random>

enum MapType {
	kBlank = 0,
	kBlock = 1,
	kHole = 2,
	kBorder = 3,
	kPlayer = 4,
	kGoal = 5
};

struct IndexSet {
	int xIndex;
	int yIndex;
	// コンストラクタを追加
	IndexSet(int x = 0, int y = 0) : xIndex(x), yIndex(y) {}
};

class MapField
{
public:
	static inline const float kBlockWidth = 32.0f;
	static inline const float kBlockHeight = 32.0f;
	static inline const int kNumBlockVirtical = 20; // 縦
	static inline const int kNumBlockHorizontal = 20; // 横

	// コンストラクタなど

	void ResetMapChipData();
	void GenerateRandomObstacles(int blockNum2x2, int blockNum3x3, int holeNum3x2, int holeNum4x3);

	// ゲッター関数
	MapType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) const;
	Vector2 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) const;
	Vector2 GetPositionByIndexSet(const IndexSet& indexSet) const;
	std::vector<std::vector<int>> mapData_;
	std::random_device rd_;
	std::mt19937 rng_;

	void InitializeMapData();
	void AddBorder();
	void PlaceObject(int width, int height, MapType type);
};
