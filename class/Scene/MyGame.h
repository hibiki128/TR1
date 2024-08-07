#pragma once
#include"./class/Char/Player.h"
class MyGame
{
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	MyGame();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MyGame();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	/// <summary>
	/// ブロック生成
	/// </summary>
	void GenerateBlocks();

private:

	// クラス宣言
	MapField* mapField_ = nullptr;
	Player* player_ = nullptr;

	Vector2Int mousePosition_ = {};
	Vector2 point = {};

	// ブロックの数
	int blockNum2x2 = 0;
	int blockNum3x3 = 0;
	int holeNum3x2 = 0;
	int holeNum4x3 = 0;
};

