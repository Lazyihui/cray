#ifndef RoleEntity_Input_H
#define RoleEntitu_Input_H
#include "../include/raymath.h"
#include "../include/raylib.h"
#include "RoleEntity.h"
#include "stdio.h"

Rectangle RectNew(float x, float y, float width, float height) {
    return (Rectangle){.x = x, .y = y, .width = width, .height = height};
}

Rectangle RoleEntity_GetRect(RoleEntity *role) {
    return RectNew(role->pos.x, role->pos.y, role->width, role->height);
}

void RoleEntity_Input(RoleEntity *role) {
    Vector2 moveInput = (Vector2){0}; //??
    if (IsKeyDown(KEY_W)) {
        moveInput.y = -1;
    }
    if (IsKeyDown(KEY_S)) {
        moveInput.y = 1;
    }
    if (IsKeyDown(KEY_A)) {
        moveInput.x = -1;
    }
    if (IsKeyDown(KEY_D)) {
        moveInput.x = 1;
    }
    role->moveAxis = Vector2Normalize(moveInput);
}
void RoleEntity_InputG(RoleEntity *role) {
    Vector2 moveInput = role->moveAxis;

    if (role->pos.x < 0) {
        moveInput.x = 1;
    }

    if (role->pos.x > 900) {
        moveInput.x = -1;
    }

    if (moveInput.x == 0) {
        moveInput.x = 1; //
    }

    role->moveAxis = Vector2Normalize(moveInput); //化一
}

void RoleEntity_InputB(Bullet *Bullet) {
    Vector2 moveInput = {0}; 
    if (IsKeyDown(KEY_K)) {
        moveInput.y = -1;
    }
    Bullet->moveAxis = Vector2Normalize(moveInput);
}

#endif