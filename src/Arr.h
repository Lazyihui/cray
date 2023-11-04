#ifndef Arr_H
#define Arr_H
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "stdio.h"
#define WIDTH 500 // 定义一个常量
#define HEIGHT 500

int GetIndex(int indexwidth, int x, int y) {
    return x + indexwidth * y;
}
// *arr   or  arr[]   数组

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


#endif