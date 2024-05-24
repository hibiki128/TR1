#pragma once
#include "cstdint"
#include "string"
#include "vector"
#include "Vector3.h"

enum class MapChipType {
    kBlank, // 空白
    kBlock, // ブロック
    kBorder,
    kHole
};

struct MapChipData {
    std::vector<std::vector<MapChipType>> data;
};

struct IndexSet {
    uint32_t xIndex;
    uint32_t yIndex;
};

class MapChipField
{
private:
    // 1ブロックのサイズ
    static inline const float kBlockWidth = 16.0f;
    static inline const float kBlockHeight = 16.0f;
    // ブロックの個数
    static inline const uint32_t kNumBlockVirtical = 25; // 縦
    static inline const uint32_t kNumBlockHorizontal = 80; // 横

    MapChipData mapChipData_;

public:

    struct Rect {
        float left;   // 左端
        float right;  // 右端
        float bottom; // 下端
        float top;    // 上端
    };

    void ResetMapChipData();

    //void LoadMapChipCsv(const std::string& filePath);

    MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

    Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

    uint32_t GetNumBlockVirtical() { return kNumBlockVirtical; };
    uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; };
    float GetBlockWidth() { return kBlockWidth; };
    float GetBlockHeight() { return kBlockHeight; };

    IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

    Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

    void GenerateRandomObstacles(int blockNum2x2, int blockNum3x3, int holeNum3x2, int holeNum4x3);

};

