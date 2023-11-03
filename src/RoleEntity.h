#ifndef RoleEntity_H
#define RoleEntity_H
#include "../include/raylib.h"
#include "../include/raymath.h"

typedef struct Bullet {
    Vector2 moveAxis;
    float moveSpeed;
    Vector2 pos;
    float radius;
    Color color;
} Bullet;

typedef struct RoleEntity {
    Vector2 moveAxis;
    float moveSpeed;
    Vector2 pos;
    int width;
    int height;
    Color color;
} RoleEntity;



void RoleEntity_DrawB(Bullet *Bullet) {
    DrawCircle(Bullet->pos.x, Bullet->pos.y, Bullet->radius, Bullet->color);
}

void RoleEntity_Draw(RoleEntity *role) {
    DrawRectangle(role->pos.x, role->pos.y, role->width, role->height, role->color);
}



#endif