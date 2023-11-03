#include "../include/raylib.h"
#include "../include/raymath.h"
#include "stdio.h"
#include "RoleEntity.h"
#include "RoleEntity_Inpupt.h"
#include "RoleEntity_Move.h"
#include "stdlib.h"
#include "time.h"
#define WIDTH 50 // 定义一个常量
#define HEIGHT 3

bool IsPointInsideRect(Vector2 pos, Vector2 rectanglePoint, Vector2 rectangleSize) {
    if (pos.x > rectanglePoint.x && pos.x < rectanglePoint.x + rectangleSize.x && pos.y > rectanglePoint.y &&
        pos.y < rectanglePoint.y + rectangleSize.y) {
        return true;
    } else {
        return false;
    }
}

bool ISPointsideCircle(Vector2 pos, Vector2 circlepoint, float circleradius) {

    if ((pos.x - circlepoint.x) * (pos.x - circlepoint.x) + (pos.y - circlepoint.y) * (pos.y - circlepoint.y) <=
        circleradius * circleradius) {
        return true;
    } else {
        return false;
    }
}

int GetIndex(int indexwidth, int x, int y) {
    return x + indexwidth * y;
} //*arr   or  arr[]   数组

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
        Vector2 pos = GetMousePosition();
        

        // YELLOW
        if (status == 0) {
            arr[index] = 1;
            index += 1;
            if (index >= WIDTH * HEIGHT) {
                status = 1;
                index = WIDTH * HEIGHT -1;
            }
        } else if (status == 1) {
            arr[index] = 2;
            index -= 1;
            if (index < 0) {
                status = 0;
                index = 0;
            }
        }
        
        // BLUE

        DrawArr(arr, WIDTH, HEIGHT);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
