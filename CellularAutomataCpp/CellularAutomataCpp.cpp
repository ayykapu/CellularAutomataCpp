#include "raylib.h"
#include <iostream>
#include <list>
#include <chrono>
#include <thread>
#include <vector>
#include <conio.h>


int windowWidth = 1920, windowHeight = 1080;
int pixelSize = 10;
int xGrid, yGrid;

void Init();
void DrawFixedPixel(int x, int y, Color c);
void GlobalUpdate();
void ProcessCells();
void DrawCells();
void DisplayGrid();
int GetRandomNumber(int minInc, int maxExc);
void Spawn(int type, int x, int y, int delay);
int spawnerDelay = 0;
std::vector<int> GetRandomDistinctPairs(int minIncX, int maxExcX, int minIncY, int maxExcY, int count);

// hack
void TEMPBuildTerrain();
// hack
void TEMPBuildSand();

int grid[108][192];
int newGrid[108][192];

int main() {

    Init();
	TEMPBuildTerrain();

	GlobalUpdate();
    CloseWindow();

    return 0;
}

void Init() {

    InitWindow(windowWidth, windowHeight, "Skibidi Automata");
    SetTargetFPS(60);
    srand(time(nullptr));

	xGrid = sizeof(grid[0]) / sizeof(grid[0][0]);
	yGrid = sizeof(grid) / sizeof(grid[0]);

    system("cls");
}

void DrawFixedPixel(int height, int width, Color c) {

    for (int y = height * pixelSize; y < (height + 1) * pixelSize; y++) {

        for (int x = width * pixelSize; x < (width + 1) * pixelSize; x++) {

            DrawPixel(x, y, c);
        }
    }
}

void GlobalUpdate() {

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground( { 200, 200, 200, 255 } );

        DrawCells();
        EndDrawing();
        Spawn(2, 106, 10, 20);
        ProcessCells();
        
        if (IsKeyDown(KEY_ONE)) {

            TEMPBuildSand();
        }
        
    }
}

void ProcessCells() {

    for (int y = 0; y < yGrid; y++) {
    
        for (int x = 0; x < xGrid; x++) {

			//GROUND
			if (grid[y][x] == 1) {

				newGrid[y][x] = 1;
			}

            //SAND
            if (grid[y][x] == 2) {
                
				if (grid[y + 1][x] == 0) {

                    newGrid[y][x] = 0;
					newGrid[y + 1][x] = 2;
                }
                else {

                    int rand = GetRandomNumber(0, 2);

                    if (rand == 1) {

                        if (grid[y + 1][x - 1] == 0) {

							newGrid[y][x] = 0;
							newGrid[y + 1][x - 1] = 2;
                        }
                        else if (grid[y + 1][x + 1] == 0) {

                            newGrid[y][x] = 0;
                            newGrid[y + 1][x + 1] = 2;
                        }
                        else {

                            newGrid[y][x] = 2;
                        }
                    }
                    else {

                        if (grid[y + 1][x + 1] == 0) {

                            newGrid[y][x] = 0;
                            newGrid[y + 1][x + 1] = 2;
                        }
                        else if (grid[y + 1][x - 1] == 0) {

                            newGrid[y][x] = 0;
                            newGrid[y + 1][x - 1] = 2;
                        }
                        else {

                            newGrid[y][x] = 2;
                        }
                    }
                }
            }

        }
    }

    for (int i = 0; i < yGrid; i++) {

        std::copy(newGrid[i], newGrid[i] + xGrid, grid[i]);
    }
}

void DrawCells() {

    for (int y = 0; y < yGrid; y++) {

        for (int x = 0; x < xGrid; x++) {

			if (grid[y][x] == 1) {
				
                DrawFixedPixel(y, x, BLACK);
			}
			else if (grid[y][x] == 2) {
				
                DrawFixedPixel(y, x, YELLOW);
            }
        }
    }
}

void TEMPBuildTerrain() {

    for (int i = 0; i < xGrid; i++) {

        grid[yGrid - 1][i] = 1;
    }

    for (int y = 50; y < 52; y++) {

        for (int x = 104; x < 112; x++) {
            
            grid[y][x] = 1;
        }
    }

    for (int y = 60; y < 62; y++) {
        
        for (int x = 44; x < 49; x++) {

            grid[y][x] = 1;
        }
    }

    for (int y = 59; y < 61; y++) {

        for (int x = 43; x < 45; x++) {

            grid[y][x] = 1;
        }

        for (int x = 48; x < 50; x++) {

            grid[y][x] = 1;
        }
    }

    for (int y = 80; y < 86; y++) {

        for (int x = 30; x < 32; x++) {

            grid[y][x] = 1;
        }

        for (int x = 53; x < 55; x++) {

            grid[y][x] = 1;
        }
    }

    for (int y = 86; y < 88; y++) {

        for (int x = 30; x < 55; x++) {

            grid[y][x] = 1;
        }
    }

	int tilt = 40;

    for (int y = 40; y < 43; y++) {

        for (int x = 150; x < 175; x++) {

            grid[y + tilt][x] = 1;
            tilt--;
        }

		tilt = 40;
    }

    grid[81][149] = 1;
    grid[82][149] = 1;

    grid[56][175] = 1;
    grid[57][175] = 1;

}

//adds 100 sand cells at random positions
void TEMPBuildSand() {

    std::vector<int>newSandCells = GetRandomDistinctPairs(0, 192, 0, 50, 100);

	for (int i = 0; i < newSandCells.size(); i += 2) {
		
        grid[newSandCells[i + 1]][newSandCells[i]] = 2;
	}
}

void DisplayGrid() {
	
    system("cls");

    for (int y = 0; y < yGrid; y++) {
		
        for (int x = 0; x < xGrid; x++) {
			
            std::cout << grid[y][x] << " ";
		}

		std::cout << std::endl;
	}
}

int GetRandomNumber(int minInc, int maxExc) {

    return minInc + rand() % (maxExc - minInc);
}

void Spawn(int type, int x, int y, int delay) {

    //Spawn(2, 106, 10, 20);
    if (spawnerDelay == delay) {

        newGrid[y][x] = type;
        newGrid[y + 10][x + 10] = type;
        newGrid[y + 20][x - 20] = type;
        newGrid[y + 20][x - 60] = type;
        newGrid[y][x + 60] = type;

        spawnerDelay = 0;
    }

	spawnerDelay++;
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