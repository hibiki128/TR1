#include "Pathfinding.h"

Pathfinding::Pathfinding(int gridSize)
    : gridSize(gridSize), gen(rd()), disX(0.0f, 1000.0f), disY(0.0f, 640.0f) {
    grid = new Vertex * [gridSize];
    for (int i = 0; i < gridSize; ++i) {
        grid[i] = new Vertex[gridSize];
    }
}

Pathfinding::~Pathfinding() {
    for (int i = 0; i < gridSize; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Pathfinding::InitializeVertices() {
    // ����������
    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            grid[y][x].x = disX(gen);
            grid[y][x].y = disY(gen);
            astar.vertices.push_back(&grid[y][x]);
        }
    }

    // �אڃ��X�g�̐ݒ�
    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            grid[y][x].neighbors.clear();
            if (x > 0) grid[y][x].neighbors.push_back(&grid[y][x - 1]); // ��
            if (x < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y][x + 1]); // �E
            if (y > 0) grid[y][x].neighbors.push_back(&grid[y - 1][x]); // ��
            if (y < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y + 1][x]); // ��
        }
    }
}

void Pathfinding::RandomizeVertices() {
    // �����_���z�u
    astar.vertices.clear();
    InitializeVertices(); // ���������s���ă����_���ȍ��W��ݒ�

    // �אڃ��X�g�̍Đݒ�
    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            grid[y][x].neighbors.clear();
            if (x > 0) grid[y][x].neighbors.push_back(&grid[y][x - 1]); // ��
            if (x < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y][x + 1]); // �E
            if (y > 0) grid[y][x].neighbors.push_back(&grid[y - 1][x]); // ��
            if (y < gridSize - 1) grid[y][x].neighbors.push_back(&grid[y + 1][x]); // ��
        }
    }
}

void Pathfinding::SetStart(Vertex* start) {
    this->start = start;
}

void Pathfinding::SetGoal(Vertex* goal) {
    this->goal = goal;
}

void Pathfinding::StartAStarSearch() {
    if (start && goal) {
        // A*�T���J�n
        std::vector<Vertex*> path = astar.a_star(start, goal);
        pathEdges.clear();
        exploredEdges = astar.exploredEdges;

        // �p�X���G�b�W�ɕϊ�
        for (size_t i = 0; i < path.size() - 1; ++i) {
            pathEdges.push_back({ path[i], path[i + 1] });
        }
    }
}

void Pathfinding::Draw()
{
    DrawGrid();
    DrawPath();
    DrawStartAndGoal();
}

void Pathfinding::DrawGrid() {
    // �O���b�h�̕`��
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
}

void Pathfinding::DrawPath() {
    // �p�X�̕`��
    for (const auto& edge : pathEdges) {
        Novice::DrawLine(
            static_cast<int>(edge.first->x), static_cast<int>(edge.first->y),
            static_cast<int>(edge.second->x), static_cast<int>(edge.second->y),
          GREEN
        );
    }
}

void Pathfinding::DrawStartAndGoal() {
    // �X�^�[�g�ƃS�[���̕`��
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
}