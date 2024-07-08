#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

struct Vertex {
    bool isClosed = false;
    Vertex* previous = nullptr;
    std::vector<Vertex*> neighbors;
    float x, y; // 2Dグリッド上の座標
    // その他のプロパティ
};

struct Node {
    Vertex* target;
    Vertex* parent;
    float g;
    float f;

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

class Astar {
public:
    std::vector<Vertex*> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> exploredEdges;

    float real_cost(Vertex* a, Vertex* b);
    float heuristic_cost(Vertex* a, Vertex* b);

    void resetVertices();

    std::vector<Vertex*> a_star(Vertex* start, Vertex* goal);
};