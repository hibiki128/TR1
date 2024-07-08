#include <Novice.h>
#include <random>
#include "imgui.h"
#include "math/Astar.h"
#include <string>

const char kWindowTitle[] = "LE2B_20_ハギワラ_ヒビキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Astar astar;

	// 乱数生成器の初期化
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(0.0f, 1000.0f);
	std::uniform_real_distribution<float> disY(0.0f, 640.0f);

	// 10x10グリッドの頂点を作成
	int gridSize = 3;
	Vertex grid[3][3];

	// 頂点の座標をランダムに設定する関数
	auto randomizeVertices = [&]() {
		astar.vertices.clear(); // 現在の頂点をクリア

		for (int y = 0; y < gridSize; ++y) {
			for (int x = 0; x < gridSize; ++x) {
				grid[y][x].x = disX(gen);
				grid[y][x].y = disY(gen);
				astar.vertices.push_back(&grid[y][x]);
			}
		}

		// 隣接リストを再設定
		for (int y = 0; y < gridSize; ++y) {
			for (int x = 0; x < gridSize; ++x) {
				grid[y][x].neighbors.clear(); // 隣接リストをクリア

				if (x > 0) grid[y][x].neighbors.push_back(&grid[y][x - 1]); // 左
				if (x < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y][x + 1]); // 右
				if (y > 0) grid[y][x].neighbors.push_back(&grid[y - 1][x]); // 上
				if (y < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y + 1][x]); // 下
			}
		}
		};

	randomizeVertices(); // 初期ランダム配置

	// スタートとゴールを設定
	Vertex* start = &grid[0][0];
	Vertex* goal = &grid[2][2];

	bool StartSearch = false;
	std::vector<std::pair<Vertex*, Vertex*>> pathEdges;
	std::vector<std::pair<Vertex*, Vertex*>> exploredEdges;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1000, 640);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			StartSearch = true;
		}
		if (keys[DIK_R] && !preKeys[DIK_R]) {
			randomizeVertices(); // ランダムで頂点を再設定
			StartSearch = false; // 探索をリセット
		}
		if (StartSearch) {
			// A* アルゴリズムを実行
			std::vector<Vertex*> path = astar.a_star(start, goal);
			pathEdges.clear();
			exploredEdges.clear();
			for (size_t i = 0; i < path.size() - 1; ++i) {
				pathEdges.push_back({ path[i], path[i + 1] });
			}
			for (const auto& edge : exploredEdges) {
				if (std::find(pathEdges.begin(), pathEdges.end(), edge) == pathEdges.end()) {
					pathEdges.push_back(edge);
				}
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// すべてのエッジを白で描画
		for (int y = 0; y < gridSize; ++y) {
			for (int x = 0; x < gridSize; ++x) {
				for (Vertex* neighbor : grid[y][x].neighbors) {
					Novice::DrawLine(
						static_cast<int>(grid[y][x].x), static_cast<int>(grid[y][x].y),
						static_cast<int>(neighbor->x), static_cast<int>(neighbor->y),
						WHITE
					);
				}
			}
		}

		if (StartSearch) {
			// 探索済みのエッジを黒で描画
			for (const auto& edge : astar.exploredEdges) {
				Novice::DrawLine(
					static_cast<int>(edge.first->x), static_cast<int>(edge.first->y),
					static_cast<int>(edge.second->x), static_cast<int>(edge.second->y),
					BLACK
				);
			}
			// 最短経路を緑で描画
			for (const auto& edge : pathEdges) {
				Novice::DrawLine(
					static_cast<int>(edge.first->x), static_cast<int>(edge.first->y),
					static_cast<int>(edge.second->x), static_cast<int>(edge.second->y),
					GREEN
				);
			}
		}

		// スタートとゴールのグリッドを色分けして描画
		for (int y = 0; y < gridSize; ++y) {
			for (int x = 0; x < gridSize; ++x) {
				int drawX = static_cast<int>(grid[y][x].x);
				int drawY = static_cast<int>(grid[y][x].y);

				if (&grid[y][x] == start) {
					Novice::DrawEllipse(drawX, drawY, 5, 5, 0.0f, RED, kFillModeSolid);
				}
				else if (&grid[y][x] == goal) {
					Novice::DrawEllipse(drawX, drawY, 5, 5, 0.0f, BLUE, kFillModeSolid);
				}
				else {
					Novice::DrawEllipse(drawX, drawY, 5, 5, 0.0f, WHITE, kFillModeSolid);
				}
			}
		}

		ImGui::Begin(" ");
		// 各gridの座標をドラッグできるようにする
		for (int y = 0; y < gridSize; ++y) {
			for (int x = 0; x < gridSize; ++x) {
				ImGui::DragFloat2(std::to_string(y * gridSize + x).c_str(), &grid[y][x].x, 0.1f);
			}
		}
		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}