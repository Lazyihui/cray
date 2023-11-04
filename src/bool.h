#ifndef BOOL_H
#define BOOL_H 
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "stdio.h"
#include "RoleEntity.h"
#include "RoleEntity_Inpupt.h"
#include "RoleEntity_Move.h"
#include "stdlib.h"
#include "time.h"

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



#endif