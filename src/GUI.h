#ifndef GUI_H__
#define GUI_H__
#include "../include/raylib.h"
#include "RockEntity.h"
#include "HookEntity.h"
#include "common.h"
#include "Context.h"
#include "stdio.h"
//    方块  文字  鼠标坐标  是否按下  按下的时候是否处于方块内
bool GUI_Button(Vector2 rectangle, Vector2 rectanglesize, Color rectanglecolor, const char *pressname, Vector2 press,
                int presssize, Color presscolor) {
                    
    DrawRectangle(rectangle.x, rectangle.y, rectanglesize.x, rectanglesize.y, BLACK);
    DrawText(pressname, press.x, press.y, presssize, presscolor);
    Vector2 clickmouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        printf("yes");
        if ((clickmouse.x > rectangle.x) && (clickmouse.x < (rectangle.x + rectanglesize.x)) &&
            (clickmouse.y > rectangle.y) && (clickmouse.y < (rectangle.y + rectanglesize.y))) {

            return true;
        }
    }
    return false;
}

#endif