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

typedef struct Circle {
    Vector2 moveAxis;
    float moveSpeed;
    Vector2 pos;
    float radius;
    Color color;

} Circle;


void RoleEntity_DrawB(Bullet *Bullet) {
    DrawCircle(Bullet->pos.x, Bullet->pos.y, Bullet->radius, Bullet->color);
}

void RoleEntity_Draw(RoleEntity *role) {
    DrawRectangle(role->pos.x, role->pos.y, role->width, role->height, role->color);
}

void RoleEntity_DrawBlack(RoleEntity *role) {
    DrawRectangle(role->pos.x, role->pos.y, role->width, role->height, BLACK);
}

void RoleEntity_DrawCircle(Circle *Circle) {
    DrawCircle(Circle->pos.x, Circle->pos.y, Circle->radius, Circle->color);
}



#endif