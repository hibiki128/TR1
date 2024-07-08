#include "Astar.h"

float Astar::real_cost(Vertex* a, Vertex* b) {
    // 2つの頂点間のマンハッタン距離を計算
    return std::abs(a->x - b->x) + std::abs(a->y - b->y);
}

float Astar::heuristic_cost(Vertex* a, Vertex* b) {
    // 2つの頂点間のユークリッド距離を計算
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    return std::sqrt(dx * dx + dy * dy);
}

void Astar::resetVertices() {
    for (auto& vertex : vertices) {
        vertex->isClosed = false;
        vertex->previous = nullptr;
    }
    exploredEdges.clear(); // 探索したエッジをリセット
}

std::vector<Vertex*> Astar::a_star(Vertex* start, Vertex* goal) {
    resetVertices(); // 各探索の前にリセット

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> queue;
    Node start_node = { start, nullptr, 0, 0 };
    queue.push(start_node);

    while (!queue.empty()) {
        Node node = queue.top();
        queue.pop();

        if (node.target->isClosed) continue;

        node.target->isClosed = true;
        node.target->previous = node.parent;

        if (node.target == goal) {
            std::vector<Vertex*> total_path;
            Vertex* vertex = goal;
            while (vertex != nullptr) {
                total_path.push_back(vertex);
                vertex = vertex->previous;
            }
            std::reverse(total_path.begin(), total_path.end()); // 経路を逆順にする
            return total_path;
        }

        for (Vertex* neighbor : node.target->neighbors) {
            if (neighbor->isClosed) continue;

            Node new_node;
            new_node.parent = node.target;
            new_node.target = neighbor;
            new_node.g = node.g + real_cost(node.target, neighbor);
            new_node.f = new_node.g + heuristic_cost(neighbor, goal);

            queue.push(new_node);

            // 探索したエッジを追加
            exploredEdges.push_back({ node.target, neighbor });
        }
    }

    return {}; // ゴールに到達できなかった場合、空の経路を返す
}