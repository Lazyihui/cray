#ifndef ROCKENTITY_H__
#define ROCKENTITY_H__
#include "../include/raylib.h"

typedef struct Rock {
    float heavy;
    Vector2 pos;
    Color color;
    float radius;
    int gold; // byte
} Rock;

void Rock_Draw(Rock *Rock) {
    DrawCircle(Rock->pos.x, Rock->pos.y, Rock->radius, Rock->color);
}


void Rock_Gold(Rock rock) {
    const char *a = TextFormat("%d", rock.gold);
    DrawText(a, 420, 51, 20, YELLOW);
}






#endif