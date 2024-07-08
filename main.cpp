#include <Novice.h>
#include <random>
#include "imgui.h"
#include "math/Astar.h"
#include "math/Vector2.h" // 追加
#include <string>

const char kWindowTitle[] = "LE2B_20_ハギワラ_ヒビキ";

// マウスの判定距離
const float kClickDistance = 5.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Astar astar;

    // 乱数生成器の初期化
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(0.0f, 1000.0f);
    std::uniform_real_distribution<float> disY(0.0f, 640.0f);

    // 10x10グリッドの頂点を作成
    int gridSize = 5;
    Vertex grid[5][5];
    float spacing = 50.0f;

    // 頂点の座標を設定
    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            grid[y][x].x = float(spacing * x+500);
            grid[y][x].y = float(spacing * y+320);
            astar.vertices.push_back(&grid[y][x]);
        }
    }

    // 隣接リストを設定
    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            if (x > 0) grid[y][x].neighbors.push_back(&grid[y][x - 1]); // 左
            if (x < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y][x + 1]); // 右
            if (y > 0) grid[y][x].neighbors.push_back(&grid[y - 1][x]); // 上
            if (y < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y + 1][x]); // 下
        }
    }

    //// 頂点の座標をランダムに設定する関数
    //auto randomizeVertices = [&]() {
    //    astar.vertices.clear(); // 現在の頂点をクリア

    //    for (int y = 0; y < gridSize; ++y) {
    //        for (int x = 0; x < gridSize; ++x) {
    //            grid[y][x].x = disX(gen);
    //            grid[y][x].y = disY(gen);
    //            astar.vertices.push_back(&grid[y][x]);
    //        }
    //    }

    //    // 隣接リストを再設定
    //    for (int y = 0; y < gridSize; ++y) {
    //        for (int x = 0; x < gridSize; ++x) {
    //            grid[y][x].neighbors.clear(); // 隣接リストをクリア

    //            if (x > 0) grid[y][x].neighbors.push_back(&grid[y][x - 1]); // 左
    //            if (x < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y][x + 1]); // 右
    //            if (y > 0) grid[y][x].neighbors.push_back(&grid[y - 1][x]); // 上
    //            if (y < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y + 1][x]); // 下
    //        }
    //    }
    //    };

    //randomizeVertices(); // 初期ランダム配置

    // スタートとゴールを設定
    Vertex* start = &grid[0][0];
    Vertex* goal = &grid[2][2];
    // 障害物を設定
    std::vector<Vertex*> obstacles(3, nullptr); // サイズを3に設定
    Vertex* selectedVertex = nullptr;

    bool StartSearch = false;
    std::vector<std::pair<Vertex*, Vertex*>> pathEdges;
    std::vector<std::pair<Vertex*, Vertex*>> exploredEdges;

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1000, 640);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // マウスの位置を取得するための変数
    int mouseX = 0;
    int mouseY = 0;

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // マウスの位置を更新
        Novice::GetMousePosition(&mouseX, &mouseY);

        ///
        /// ↓更新処理ここから
        ///

        if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
            StartSearch = true;
        }
        if (keys[DIK_R] && !preKeys[DIK_R]) {
            //randomizeVertices(); // ランダムで頂点を再設定
            StartSearch = false; // 探索をリセット
            obstacles.clear();
            obstacles.resize(3, nullptr); // サイズを3にリセット
        }
        if (StartSearch) {
            // A* アルゴリズムを実行
            std::vector<Vertex*> path = astar.a_star(start, goal,obstacles);
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

        // GキーでGoalを設定する
        if (keys[DIK_G] && !preKeys[DIK_G]) {
            // マウスの位置に最も近い頂点をGoalに設定する
            float minDistance = FLT_MAX;
            Vertex* closestVertex = nullptr;

            for (int y = 0; y < gridSize; ++y) {
                for (int x = 0; x < gridSize; ++x) {
                    float distance = Vector2::Distance(Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY)), Vector2(grid[y][x].x, grid[y][x].y));
                    if (distance < minDistance) {
                        minDistance = distance;
                        closestVertex = &grid[y][x];
                    }
                }
            }

            if (closestVertex && minDistance < kClickDistance) {
                goal = closestVertex;
                StartSearch = false; // 探索をリセット
            }
        }

        // SキーでStartを設定する
        if (keys[DIK_S]&&!preKeys[DIK_S]) {
            // マウスの位置に最も近い頂点をStartに設定する
            float minDistance = FLT_MAX;
            Vertex* closestVertex = nullptr;

            for (int y = 0; y < gridSize; ++y) {
                for (int x = 0; x < gridSize; ++x) {
                    float distance = Vector2::Distance(Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY)), Vector2(grid[y][x].x, grid[y][x].y));
                    if (distance < minDistance) {
                        minDistance = distance;
                        closestVertex = &grid[y][x];
                    }
                }
            }

            if (closestVertex && minDistance < kClickDistance) {
                start = closestVertex;
                StartSearch = false; // 探索をリセット
            }
        }

        // 1, 2, 3キーで障害物を設定する
        for (int i = 0; i < 3; ++i) {
            if (keys[DIK_1 + i] && !preKeys[DIK_1 + i]) {
                float minDistance = FLT_MAX;
                Vertex* closestVertex = nullptr;

                for (int y = 0; y < gridSize; ++y) {
                    for (int x = 0; x < gridSize; ++x) {
                        float distance = Vector2::Distance(Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY)), Vector2(grid[y][x].x, grid[y][x].y));
                        if (distance < minDistance) {
                            minDistance = distance;
                            closestVertex = &grid[y][x];
                        }
                    }
                }

                if (closestVertex && minDistance < kClickDistance) {
                    obstacles[i] = closestVertex;
                    StartSearch = false; // 探索をリセット
                }
            }
        }

        // 左クリックで頂点を選択/解除
        if (Novice::IsTriggerMouse(0)) {
            if (selectedVertex == nullptr) {
                // 最も近い頂点を選択
                float minDistance = FLT_MAX;
                for (int y = 0; y < gridSize; ++y) {
                    for (int x = 0; x < gridSize; ++x) {
                        float distance = Vector2::Distance(Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY)), Vector2(grid[y][x].x, grid[y][x].y));
                        if (distance < minDistance) {
                            minDistance = distance;
                            selectedVertex = &grid[y][x];
                        }
                    }
                }
                // クリック距離が閾値以下なら選択
                if (minDistance >= kClickDistance) {
                    selectedVertex = nullptr;
                }
            }
            else {
                // 選択解除
                selectedVertex = nullptr;
            }
        }

        // 選択された頂点があればマウスの位置に追従
        if (selectedVertex) {
            selectedVertex->x = static_cast<float>(mouseX);
            selectedVertex->y = static_cast<float>(mouseY);
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
                    Novice::DrawEllipse(drawX, drawY, 5, 5, 0.0f, BLUE, kFillModeSolid);
                }
                else if (&grid[y][x] == goal) {
                    Novice::DrawEllipse(drawX, drawY, 5, 5, 0.0f, 0xffff00ff, kFillModeSolid);
                }
                else if (std::find(obstacles.begin(), obstacles.end(), &grid[y][x]) != obstacles.end()) {
                    Novice::DrawEllipse(drawX, drawY, 5, 5, 0.0f, RED, kFillModeSolid); // 障害物を赤色で描画
                }
                else {
                    Novice::DrawEllipse(drawX, drawY, 5, 5, 0.0f, WHITE, kFillModeSolid);
                }
            }
        }

        // ImGuiウィンドウの描画
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