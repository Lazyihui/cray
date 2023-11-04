#include "../include/raylib.h"
#include "../include/raymath.h"
#include "stdio.h"
// #include "RoleEntity.h"
// #include "RoleEntity_Inpupt.h"
// #include "RoleEntity_Move.h"
// #include "stdlib.h"
// #include "time.h"
// #include "bool.h"
#define WIDTH 500 // 定义一个常量
#define HEIGHT 500

int GetIndex(int indexwidth, int x, int y) {
    return x + indexwidth * y;
}
*arr   or  arr[]   数组

void DrawArr(int *arr, int width, int height) {
    for (int x = 0; x < width; x += 1) {
        for (int y = 0; y < height; y += 1) {
            int index = GetIndex(width, x, y);
            if (arr[index] == 0) {
                DrawPixel(x, y, RED);
            } else if (arr[index] == 1) {
                DrawPixel(x, y, YELLOW);
            } else if (arr[index] == 2) {
                DrawPixel(x, y, BLUE);
            }
        }
    }
    int index = 0;
    int status = 0;
}


void DrawArr3(int *arr, int widthx, int heighty,int starty) {
    for (int x = 0; x < widthx; x += 5) {
        for (int y = starty; y < heighty; y += 0) {
            int index = GetIndex(widthx, x, y);

            if (arr[index] == 0) {
                
                    for (int longx = 6; longx < widthx; longx += 2) {
                    DrawRectangle(x, y, longx, longx, GREEN);
                    arr[index] = 1;
                    index += 2*index-1;
                }
                if (index >= WIDTH * HEIGHT) {
                    index = 0;
                }
            }
        }
    }
}

void DrawArr2(int *arr, int widthx, int heighty) {
    for (int x = 0; x < widthx; x += 3) {
        for (int y = 0; y < heighty; y += 1) {
            int index = GetIndex(widthx, x, y);
            if (arr[index] == 1) {
                DrawPixel(x, y, PURPLE);

                arr[index] = 1;
                index += 1;
                if (index >= WIDTH * HEIGHT) {
                    index = 0;
                }
            }
        }
    }
}

int main(void) {
    InitWindow(800, 450, "cyh");

    int arr[WIDTH * HEIGHT] = {0}; // 1 1 1 1 0

    int index = 0;

    SetTargetFPS(60);

    int status = 0;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        BeginDrawing();

        YELLOW
        if (status == 0) {
            arr[index] = 1;
            index += 1; // index 150>=150         其实是149结束 0 1 2 3 4......149
            if (index >= WIDTH * HEIGHT) {
                status = 1;
                index = WIDTH * HEIGHT - 1; //=149
            }
        } else if (status == 1) {
            arr[index] = 2;
            index -= 1; // 到0的时候重新开始；
            if (index < 0) {
                status = 0;
                index = 0;
            }
        }
        BLUE

        DrawArr(arr, WIDTH, HEIGHT);
        DrawArr3(arr,WIDTH,HEIGHT,250);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
