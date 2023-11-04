#ifndef HOOKENTITY_H__
#define HOOKENTITY_H__
#include "../include/raylib.h"



typedef struct Hook {
    float speed;
    Color color;
    float radius;
    Vector2 pos;
    float moveAxis;
    float angle;

} Hook;


void Hook_Draw(Hook *Hook) {
    DrawCircle(Hook->pos.x, Hook->pos.y, Hook->radius, Hook->color);
}







#endif