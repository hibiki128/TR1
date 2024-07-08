#pragma once

#include <vector>
#include <random>
#include "Novice.h"
#include "Astar.h"

struct Vertex {
    float x;
    float y;
    std::vector<Vertex*> neighbors;
};

class Pathfinding {
public:
    Pathfinding(int gridSize);
    ~Pathfinding();

    void InitializeVertices();
    void RandomizeVertices();
    void SetStart(Vertex* start);
    void SetGoal(Vertex* goal);
    void StartAStarSearch();
    void Draw();
    void DrawGrid();
    void DrawPath();
    void DrawStartAndGoal();

private:
    Astar astar;
    int gridSize;
    Vertex** grid;
    Vertex* start;
    Vertex* goal;
    std::vector<std::pair<Vertex*, Vertex*>> pathEdges;
    std::vector<std::pair<Vertex*, Vertex*>> exploredEdges;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> disX;
    std::uniform_real_distribution<float> disY;
};
