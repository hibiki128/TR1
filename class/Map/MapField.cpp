#include "MapField.h"
#include "cassert"
#include "random"
#include <iostream>

void MapField::GenerateRandomObstacles(int blockNum2x2, int blockNum3x3, int holeNum3x2, int holeNum4x3) {
    ResetMapChipData();
    InitializeMapData();
    AddBorder();

    auto placeObject = [&](int width, int height, MapType type) {
        bool placed = false;
        while (!placed) {
            int x = rng_() % (kNumBlockHorizontal - width);
            int y = rng_() % (kNumBlockVirtical - height);

            bool canPlace = true;
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    if (mapData_[x + i][y + j] != static_cast<int>(MapType::kBlank)) {
                        canPlace = false;
                        break;
                    }
                }
                if (!canPlace) break;
            }

            if (canPlace) {
                for (int i = 0; i < width; ++i) {
                    for (int j = 0; j < height; ++j) {
                        mapData_[x + i][y + j] = static_cast<int>(type);
                    }
                }
                placed = true;
            }
        }
        };

    // Place the player at {1, 1}
    mapData_[1][1] = static_cast<int>(MapType::kPlayer);

    // Place specified numbers of obstacles and holes
    for (int i = 0; i < blockNum2x2; ++i) {
        placeObject(2, 2, MapType::kBlock);
    }
    for (int i = 0; i < blockNum3x3; ++i) {
        placeObject(3, 3, MapType::kBlock);
    }
    for (int i = 0; i < holeNum3x2; ++i) {
        placeObject(3, 2, MapType::kHole);
    }
    for (int i = 0; i < holeNum4x3; ++i) {
        placeObject(4, 3, MapType::kHole);
    }
}
void MapField::ResetMapChipData() {
    InitializeMapData();  // マップデータを初期化

    // すべてのマップチップを kBlank に戻す
    for (int x = 0; x < kNumBlockHorizontal; ++x) {
        for (int y = 0; y < kNumBlockVirtical; ++y) {
            mapData_[x][y] = static_cast<int>(MapType::kBlank);
        }
    }
}

void MapField::InitializeMapData() {
    mapData_.resize(kNumBlockHorizontal, std::vector<int>(kNumBlockVirtical, static_cast<int>(MapType::kBlank)));
}

void MapField::AddBorder() {
    for (int x = 0; x < kNumBlockHorizontal; ++x) {
        mapData_[x][0] = static_cast<int>(MapType::kBorder);
        mapData_[x][kNumBlockVirtical - 1] = static_cast<int>(MapType::kBorder);
    }
    for (int y = 0; y < kNumBlockVirtical; ++y) {
        mapData_[0][y] = static_cast<int>(MapType::kBorder);
        mapData_[kNumBlockHorizontal - 1][y] = static_cast<int>(MapType::kBorder);
    }
}

MapType MapField::GetMapChipTypeByIndex(uint32_t x, uint32_t y) const {
    assert(x < kNumBlockHorizontal && y < kNumBlockVirtical);
    return static_cast<MapType>(mapData_[x][y]);
}

Vector2 MapField::GetMapChipPositionByIndex(uint32_t x, uint32_t y) const {
    assert(x < kNumBlockHorizontal && y < kNumBlockVirtical);
    return Vector2(x * kBlockWidth, y * kBlockHeight);
}

Vector2 MapField::GetPositionByIndexSet(const IndexSet& indexSet) const {
    return GetMapChipPositionByIndex(indexSet.xIndex, indexSet.yIndex);
}