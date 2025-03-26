#include "raylib.h"
#include <iostream>
#include <list>
#include <chrono>
#include <thread>
#include <vector>
#include <conio.h>


int windowWidth = 1920, windowHeight = 1080;
int pixelSize = 10;

void Init();
void DrawFixedPixel(int x, int y, Color c);
void GlobalUpdate();
void ProcessCells();
void DrawCells();
int GetRandomNumber(int minInc, int maxExc);
std::vector<int> GetRandomDistinctPairs(int minIncX, int maxExcX, int minIncY, int maxExcY, int count);

// hack
void TEMPBuildTerrain();
// hack
void TEMPBuildSand();

std::vector<int> solidCells;
int solidCellsSize;
std::vector<int> sandCells;
int sandCellsSize;


int main() {

    Init();
	TEMPBuildTerrain();
    TEMPBuildSand();

	GlobalUpdate();
    CloseWindow();

    return 0;
}

void Init() {

    InitWindow(windowWidth, windowHeight, "Non-mathematical Cellular automata");
    SetTargetFPS(60);
    srand(time(nullptr));
}

void DrawFixedPixel(int width, int height, Color c) {

    for (int i = height * pixelSize; i < (height + 1) * pixelSize; i++) {

        for (int j = width * pixelSize; j < (width + 1) * pixelSize; j++) {

            DrawPixel(j, i, c);
        }
    }
}

void GlobalUpdate() {

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground({200, 200, 200, 255});

        DrawCells();
        EndDrawing();
        ProcessCells();

        //////////////

        if (_kbhit()) {

            char key = _getch();
            
            if (key == 's') {

                TEMPBuildSand();
            }
        }
    }
}

void ProcessCells() {

    ////SAND
    for (int i = 0; i < sandCellsSize; i += 2) {

        int x = sandCells[i];
        int y = sandCells[i + 1];

        bool belowIsEmpty = true;

        for (int j = 0; j < sandCellsSize; j += 2) {
            if (sandCells[j] == x && sandCells[j + 1] == y + 1) {
                belowIsEmpty = false;
            }
        }

        for (int j = 0; j < solidCellsSize; j += 2) {
            if (solidCells[j] == x && solidCells[j + 1] == y + 1) {
                belowIsEmpty = false;
            }
        }

        if (belowIsEmpty) {
            sandCells[i + 1]++;
        }
    }
}

void DrawCells() {

    if (solidCellsSize > 1) {

        for (int i = 0; i < solidCellsSize; i += 2) {

            DrawFixedPixel(solidCells[i], solidCells[i + 1], BLACK);
        }
    }

    if (sandCellsSize > 1) {

        for (int i = 0; i < sandCellsSize; i += 2) {

            DrawFixedPixel(sandCells[i], sandCells[i + 1], YELLOW);
        }
    }
}

void TEMPBuildTerrain() {

    solidCellsSize = 384;

    for (int i = 0; i < solidCellsSize / 2; i++) {

        solidCells.push_back(i);
        solidCells.push_back(107);
    }
}

void TEMPBuildSand() {

	sandCells = GetRandomDistinctPairs(0, 192, 0, 107, 100);
	sandCellsSize = sandCells.size();
}

int GetRandomNumber(int minInc, int maxExc) {

    return minInc + rand() % (maxExc - minInc);
}

//count = -1 for random count (0-10000)
std::vector<int> GetRandomDistinctPairs(int minIncX, int maxExcX, int minIncY, int maxExcY, int count) {

    std::vector<int> result;

    if (count == -1) {
        count = GetRandomNumber(0, 10001);
    }

    int x, y;

    while (result.size() / 2 < count) {

        x = GetRandomNumber(minIncX, maxExcX);
        y = GetRandomNumber(minIncY, maxExcY);

        bool isDuplicate = false;
        for (int i = 0; i < result.size(); i += 2) {

            if (x == result[i] && y == result[i + 1]) {

                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {

            result.push_back(x);
            result.push_back(y);
        }
    }

    return result;
}